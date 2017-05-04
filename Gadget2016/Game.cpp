//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.

#include "Game.h"
#include <fstream>
#include "Utilities.h"
//Create Characters and ground rigidbody. initalize simulation.
// Passes in references to the rendering and physics engines.
Game::Game(Gadget& engine, b2World& a_world)
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


	//Create and Initalize Opponent character
	Opponent = new Character(*World);

	//Create player Character;
	Player = new Character(*World);
}

//Upates physics engine and gameplay.
void Game::Update()
{
	if(GameStopped == false)	//If the game is not over;
	{
		//update physics engine and incrememnt timer.
		World->Step(1.0f / 60.0f, 6, 2);
		timer += Engine->timer.GetElapsedTime();

		//Update opponent & Get player input.
		Opponent->Update(timer);
		Input();

		//Check if either side won
		if (Opponent->Body[0]->Body->GetPosition().x > 15)
			GameOver(false);
		else if (Player->Body[0]->Body->GetPosition().x > 15)
			GameOver(true);
	}
	else
	{
		if(Engine->mouse.GetLeftPress())
		{
			Reset();
		}
	}

}

//Takes keyboard input and moves player joints accordingly.
void Game::Input()
{
	Player->Body[0]->joints[0]->SetMotorSpeed(0.0f);
	Player->Body[0]->joints[1]->SetMotorSpeed(0.0f);

	//Contract only the joints the player chooses.
	if(Engine->keyboard.GetHold(sf::Keyboard::Key::Q))
	{
		Player->Body[0]->joints[0]->SetMotorSpeed(-3.0f);
	}
	if (Engine->keyboard.GetHold(sf::Keyboard::Key::W))
	{
		Player->Body[0]->joints[0]->SetMotorSpeed(3.0f);
	}
	if (Engine->keyboard.GetHold(sf::Keyboard::Key::O))
	{
		Player->Body[0]->joints[1]->SetMotorSpeed(-3.0f);
	}
	if (Engine->keyboard.GetHold(sf::Keyboard::Key::P))
	{
		Player->Body[0]->joints[1]->SetMotorSpeed(3.0f);
	}

}

//Renders all sprites in the scene.
void Game::Render(Shader& shader, Sprite& sprite)
{

	//Render The Opponent
	for (int i = 0; i < 3; i++) //Iterates through each character limb
	{
		shader.SetMat4("MVP", Engine->camera.GetProjection() * sprite.GetMatrix());
		shader.SetVec4("spriteUV", sprite.GetUVs());

		//Set positions, rotations, and scaling of the sprites
		sprite.SetFrame(5, 5, 64, 64, 30, false);
		sprite.SetPosition(vec3(Opponent->Body[i]->Body->GetPosition().x, Opponent->Body[i]->Body->GetPosition().y, 1.0f));
		sprite.SetScale(vec2(2 * Opponent->Body[i]->Size.x, 2 * Opponent->Body[i]->Size.y));
		sprite.SetRotation((180 / 3.14) * Opponent->Body[i]->Body->GetAngle());

		sprite.Render();
	}

	//Render The Player;
	for (int i = 0; i < 3; i++) //Iterates through each character limb
	{
		shader.SetMat4("MVP", Engine->camera.GetProjection() * sprite.GetMatrix());
		shader.SetVec4("spriteUV", sprite.GetUVs());

		//Set positions, rotations, and scaling of the sprites
		sprite.SetFrame(1, 1, 64, 64, 0, false);
		sprite.SetPosition(vec3(Player->Body[i]->Body->GetPosition().x, Player->Body[i]->Body->GetPosition().y, 1.0f));
		sprite.SetScale(vec2(2 * Player->Body[i]->Size.x, 2 * Player->Body[i]->Size.y));
		sprite.SetRotation((180 / 3.14) * Player->Body[i]->Body->GetAngle());

		sprite.Render();
	}
	
	//If the game is over.
	if(GameStopped && PlayerWin == false)
	{
		//Render Win Or Loss
		shader.SetMat4("MVP", Engine->camera.GetProjection() * sprite.GetMatrix());
		shader.SetVec4("spriteUV", sprite.GetUVs());

		//Set positions, rotations, and scaling of the sprites
		sprite.SetFrame(800, 600, 2400, 600, 2, false);
		sprite.SetPosition(vec3(0.0f, 0.0f, 1.0f));
		sprite.SetScale(vec2(7.0f, 10.0f));
		sprite.SetRotation(0.0f);

		sprite.Render();
	}
	else if (GameStopped && PlayerWin)
	{
		//Render Win Or Loss
		shader.SetMat4("MVP", Engine->camera.GetProjection() * sprite.GetMatrix());
		shader.SetVec4("spriteUV", sprite.GetUVs());

		//Set positions, rotations, and scaling of the sprites
		sprite.SetFrame(800, 600, 2400, 600, 1, false);
		sprite.SetPosition(vec3(0.0f, 0.0f, 1.0f));
		sprite.SetScale(vec2(7.0f, 10.0f));
		sprite.SetRotation(0.0f);

		sprite.Render();
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

//Triggers the game over. and sets the winner
void Game::GameOver(bool playerWon)
{
	GameStopped = true;
	PlayerWin = playerWon;
}

//Loads top Neural Net from file, and applies it to the opponent character.
void Game::Load(std::string file)
{
	//Nessisary for file I/O
	std::ifstream File(file);
	std::string Line;
	std::vector<std::string> elements;
	char delim = ' ';

	//Indexes for current layer and neuron when loading
	int layerNum = -1;
	int NeuronNum = 0;

	//current neuron weights
	std::vector<float> weights;

	//Temporary neural Net
	int sizes[3] = { 1,7,6 };
	auto TempNet = new NeuralNet(3, sizes);


	//Get and split line based on starting characters
	std::getline(File, Line);
	splitString(Line, delim, elements);
	for (int i = 0; i < elements.size(); i++)
	{
		switch (elements[i][0])
		{
		case 'L':
			layerNum++;	//If 'L' new Layer
			NeuronNum = 0;
			break;

		case 'N':		//If 'N' new neuron
			weights.clear();
			GetWeights(elements[i], weights);	//Collect neuron Weights
			TempNet->layers[layerNum].neurons[NeuronNum].w = weights;	//assign neuron weights
			NeuronNum++;
			break;
		}
	}


	delete Opponent->Brain;
	Opponent->Brain = TempNet;	//Give opponent new Neural Net.
}

void Game::Reset()
{
	timer = 0.0f;
	GameStopped = false;
	PlayerWin = false;

	Player->Reset();
	Opponent->Reset();

	World->ClearForces();
}