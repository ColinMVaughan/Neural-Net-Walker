//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.

#include "Simulation.h"
#include "Utilities.h"
#include <iostream>
#include <algorithm>
#include <fstream>

//Sort Function to sort vector of characters.
bool MySort(Character* a, Character* b)
{
	return a->score > b->score;
}

//Create Characters and ground rigidbody. initalize simulation.
// Passes in references to the rendering and physics engines.
Simulation::Simulation(Gadget& engine, b2World& a_world) 
{
	//Collect references to the physics & graphics engine.
	World = &a_world;
	Engine = &engine;


	//Set up ground physics object
	groundBodyDef.position = b2Vec2(0.0f, -10.0f);
	groundBodyDef.type = b2_staticBody;
	groundBox.SetAsBox(50.0f, 1.0f);

	//Set collision mask for the ground
	filter.categoryBits = Layer2;
	filter.maskBits = Layer1;

	//create collider for the ground
	groundBody = World->CreateBody(&groundBodyDef);
	groundBody->CreateFixture(&groundBox, 0.0f)->SetFilterData(filter);


	//Create and Initalize characters
	for(int i = 0; i< CHARACTER_NUM; i++)
	{
		character.push_back(new Character(*World));
	}
}

//Upates physics engine and characters' Neural Nets.
void Simulation::Update()
{
	//update physics engine and incrememnt timer.
	World->Step(1.0f / 60.0f, 6, 2);
	timer += Engine->timer.GetElapsedTime();

	//If enough time has past, create a new generation and reset the simulation.
	if(timer >= 20.0f)
	{
		NewGeneration();
	}

	//Update each Character
	for(int i=0; i< character.size(); i++)
	{
		character[i]->Update(timer);
	}

}

//Renders all sprites in the scene.
void Simulation::Render(Shader& shader, Sprite& sprite)
{
	//Renders each character in their current body position

	for (int n = 0; n < CHARACTER_NUM; n++)	//Iterates though each character.
	{
		for (int i = 0; i < BODY_NUM; i++) //Iterates through each character limb
		{
			shader.SetMat4("MVP", Engine->camera.GetProjection() * sprite.GetMatrix());
			shader.SetVec4("spriteUV", sprite.GetUVs());

			//Set positions, rotations, and scaling of the sprites
			sprite.SetFrame(5, 5, 64, 64, 30, false);
			sprite.SetPosition(vec3(character[n]->Body[i]->Body->GetPosition().x, character[n]->Body[i]->Body->GetPosition().y, 1.0f));
			sprite.SetScale(vec2(2 * character[n]->Body[i]->Size.x, 2 * character[n]->Body[i]->Size.y));
			sprite.SetRotation((180 / 3.14) * character[n]->Body[i]->Body->GetAngle());

			sprite.Render();
		}
	}


	shader.SetMat4("MVP", Engine->camera.GetProjection() * sprite.GetMatrix());
	shader.SetVec4("spriteUV", sprite.GetUVs());

	//Set positions, rotations, and scaling of the sprites
	sprite.SetFrame(800, 600, 2400, 600, 0, false);
	sprite.SetPosition(vec3(0.0f, 0.0f, 2.0f));
	sprite.SetScale(vec2(30.0f, 20.0f));
	sprite.SetRotation(0.0f);

	sprite.Render();
}

//Sets triggers procreation of neural nets, and creates new generation of walkers.
void Simulation::NewGeneration()
{
	float rotation = 0;
	float scoreAvg = 0;
	
	//Generates score for eaach character based on the distance they traveled.
	for(int i = 0; i< character.size(); i++)
	{
		character[i]->score = character[i]->Body[0]->Body->GetPosition().x;
		rotation = character[i]->Body[0]->Body->GetAngle();
		fabs(rotation); //get absolute value of rotation, we only care if the character is upside down.

		//check if the character is upright. if so, double score.
		//modulus rotation because box2D rotation is unbounded.
		if(fmod(rotation , 2*b2_pi) < 2  || fmod(rotation, 2*b2_pi) > 3.5)
			character[i]->score *= 2.0f;
		else
			character[i]->score *= 0.5f;


		scoreAvg += character[i]->score; // average scores.

	}


	//Sort the array of characters based on their score.
	std::sort(character.begin(), character.end(), MySort);
	std::vector<Character*> topHalf;
	std::vector<NeuralNet*> nets;
	
	if(character[0]->Body[0]->Body->GetPosition().x > 15)
	{
		CheeseIt();
	}

	SaveState("./TrainData/TestFile.txt"); // Save each neural net to a file.

	//takes the top scoring half of the characters.
	for(int i=0; i< character.size()/2; i++)
	{
		topHalf.push_back(character[i]);
	}

	//Create the new Nural Nets.
	int j;
	for (int i = 0; i< topHalf.size(); i++)
	{
		j = (i + 1) % topHalf.size();
		nets.push_back(new NeuralNet(topHalf[i]->Procreate(*topHalf[j], 1.0f)));

		j = (i + 2) % topHalf.size();
		nets.push_back(new NeuralNet(topHalf[i]->Procreate(*topHalf[j], 1.0f)));
	}


	//Reset Each Character to starting position / pose.
	for(int i=0; i<CHARACTER_NUM; i++)
	{
		character[i]->ReplaceNet(*nets[i]);
		character[i]->Reset();
	}
	World->ClearForces();

	GenNum++; //Increment number of generation
	scoreAvg = scoreAvg / character.size(); //average out the scores

	//Set the window title bar to show the current generation
	std::string title;
	title = " Generation: " + std::to_string(GenNum);
	title += " ";
	title += "AverageScore: ";
	title += std::to_string(scoreAvg);
	Engine->window.setTitle(title);

	timer = 0.0f; //Reset timer

}

//Save the states of the different characters to a File
void Simulation::SaveState(std::string filePath)
{
	std::ofstream File(filePath);
	std::string Info;


	//Loop through each character and print the weights for each neuron/layer into file
	for(int i = 0; i< character.size(); i++)
	{
		Info += " C";
		for(int l = 0; l < character[i]->Brain->layers.size(); l++)
		{
			Info += " L";
			for(int n = 0; n < character[i]->Brain->layers[l].neurons.size(); n++)
			{
				Info += " N";
				for(int w = 0; w < character[i]->Brain->layers[l].neurons[n].w.size(); w++)
				{
					Info += ",";
					Info += std::to_string(character[i]->Brain->layers[l].neurons[n].w[w]);

				}
			}
		}

		Info += "\n";
		File.write(Info.c_str(), Info.size()); //write to file;
		Info.clear();
	}
	
	File.close(); //finish saving
}

//Loads neural nets from a file. useful for multiple training sessions.
void Simulation::LoadState(std::string filePath)
{
	//Nessisary File Loading data
	std::ifstream File("");
	std::string Line;
	std::vector<std::string> elements;
	char delimitor1 = ' ';

	//Neural Net Sizes
	int sizes[3] = { 2,7,6};

	//Indexes for reading weights
	int layerNum = 0;
	int NeuronNum = 0;
	int cNum = 0;

	std::vector<float> weights;
	NeuralNet* TempNet = new NeuralNet(3, sizes);

	//Loop through each character
	while (std::getline(File,Line))
	{
		//Split line based on starting characters.
		splitString(Line, delimitor1, elements);
		for (int i = 0; i < elements.size(); i++)
		{
			switch (elements[i][0])
			{
			case 'L':
				layerNum++;		//If 'L', new Layer
				break;

			case 'N':			//If 'N' new Line.
				weights.clear();
				GetWeights(elements[i], weights);
				TempNet->layers[layerNum].neurons[NeuronNum].w = weights;	//Set Neuron Weights
				break;
			}
		}

		delete character[cNum]->Brain;
		character[cNum]->Brain = TempNet; //Give Character New Neural Net.
	}



}

void Simulation::CheeseIt()
{
	*character[9]->Brain = *character[0]->Brain;
	std::sort(character.begin(), character.end(), MySort);

}