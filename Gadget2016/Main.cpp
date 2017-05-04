////Brent Cowan 2016
//#include "Engine/Engine.h"
//#include <iostream>
//#include "Vehicle.h" //A vehicle class which adds basic physics and collision detection
//#include "NeuralNet.h" //Neural Net class
//
//#include <Box2D.h>
//int main()
//{
//
//	Gadget G; G.OpenWindow(600, 600, false, false, true); //Open window 600 X 600
//	G.window.setTitle("Generation: 0 Average Score: 0");
//	G.camera.SetZoom(10.0f); //The width of the screen in 10 units wide
//
//	Load sprite shader
//	Shader shade; shade.Load("Shaders/SpriteVert.glsl", "Shaders/SpriteFrag.glsl");
//
//	Load the gem textures
//	Texture gemTex; gemTex.Load("Resources/MarioTiles.png");
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//
//	All gems will reuse this sprite
//	Sprite gemSpr; gemSpr.SetScale(vec2(0.2f, 0.2f));
//	gemSpr.SetFrame(16, 16, 64, 64, 12, false);
//
//	Create a bunch of random gems
//	std::vector<vec2> gems;
//	for (int i = 0; i < 40; i++)
//	{
//		gems.push_back(vec2(Random(-4.5f, 4.5f), Random(-4.5f, 4.5f)));
//	}
//
//	Load the ship textures
//	Texture blueTex; blueTex.Load("Resources/BlueShip.png");
//
//	All ships will reuse this sprite
//	Sprite shipSpr; shipSpr.SetScale(vec2(0.5f, 0.5f));
//
//	Create a default vehicle
//	Vehicle::G = &G;
//	Vehicle ship;
//	ship.friction = 0.02f;
//	ship.maxRotation = 400.0f;
//	ship.maxAcceleration = 20.0f;
//	ship.maxVelocity = 2.0f;
//	ship.radius = 0.3f;
//
//	Neural net shit
//	//////////////////////////////////////////////////////////////////////////
//	create some blue ships
//	std::vector<Vehicle> ships;
//	std::vector<NeuralNet> nets;
//
//	int sizes[2] = { 2,2 };
//	float in[2];
//	float out[2];
//
//	for (int i = 0; i < 40; i++)
//	{
//		ship.direction = Random(0.0f, 360.0f);
//		ship.position.x = Random(-4.5f, 4.5f);
//		ship.position.y = Random(-4.5f, 4.5f);
//		ships.push_back(ship);
//
//		nets.push_back(NeuralNet(2, sizes));
//	}
//	
//	float score = 0.0f;
//	float averageScore = 0.0f;
//	float time = 0.0f;
//	int generation = 0;
//	float trialTime = 30.0f;
//
//	while (G.Update()) // Start the game loop
//	{
//		for (int i = 0; i < ships.size(); i++)
//		{
//			Move the blue ships
//			vec2 force = vec2(0.0f, 0.0f);
//
//			Find the nearest gem
//			vec2 nearestPos;
//			float dist = 9999.9f;
//			float testDist;
//			for (int j = 0; j < gems.size(); j++)
//			{
//				testDist = Length(gems[j] - ships[i].position);
//				if (testDist < dist)//if this is the closest gem so far
//				{
//					dist = testDist;
//					nearestPos = gems[j];
//
//					if (dist < 0.2f)//if the ship is close, collect the gem
//					{
//						gems[j] = vec2(Random(-4.5f, 4.5f), Random(-4.5f, 4.5f));
//						score += 1.0f;
//
//						nets[i].score += 1.0f;
//
//					}
//				}
//			}
//
//			Neural net shit
//			//////////////////////////////////////////////////////////////////////////
//			Prepare the input
//			nearestPos = Normalize(nearestPos - ships[i].position);
//			in[0] = nearestPos.x / 2.0f + 0.5f;
//			in[1] = nearestPos.y / 2.0f + 0.5f;
//			nets[i].Update(in, out);
//
//
//			force.x = out[0];
//			force.y = out[1];
//			force = (force*2.0f) - vec2(1.0f, 1.0f);
//
//			force = nearestPos;
//			force = Normalize(force);
//
//			ships[i].SetSteeringForce(force);
//			ships[i].SetRotation(ships[i].velocity);
//			ships[i].Update();
//
//
//			Keep the ship on screen
//			if (ships[i].position.x < -5.0f){ ships[i].position.x =  4.99f; }
//			if (ships[i].position.x >  5.0f){ ships[i].position.x = -4.99f; }
//			if (ships[i].position.y < -5.0f){ ships[i].position.y =  4.99f; }
//			if (ships[i].position.y >  5.0f){ ships[i].position.y = -4.99f; }
//
//			Set the sprite to match the vehicle
//			shipSpr.SetPosition(vec3(ships[i].position.x, ships[i].position.y, 0.0f));
//			shipSpr.SetRotation(ships[i].direction);
//
//			Render the ship
//			glDisable(GL_DEPTH_TEST);
//			shade.Activate(); //Set the active shader and variable
//			shade.Blend(2);   //Use image alpha channel
//			shade.SetMat4("MVP", G.camera.GetProjection() * shipSpr.GetMatrix());
//			shade.SetVec4("spriteUV", shipSpr.GetUVs());
//			shade.SetImage(blueTex.GetID(), "myTextureSampler", 0);
//			shipSpr.Render();
//
//		}
//		averageScore = score / float(ships.size());
//
//		Render the gems
//		for (int i = 0; i < gems.size(); i++)
//		{
//			Set the sprite to match the vehicle
//			gemSpr.SetPosition(vec3(gems[i].x, gems[i].y, 0.0f));
//
//			Render the ship
//			glDisable(GL_DEPTH_TEST);
//			shade.Activate(); //Set the active shader and variable
//			shade.Blend(2);   //Use image alpha channel
//			shade.SetMat4("MVP", G.camera.GetProjection() * gemSpr.GetMatrix());
//			shade.SetVec4("spriteUV", gemSpr.GetUVs());
//			shade.SetImage(gemTex.GetID(), "myTextureSampler", 0);
//			gemSpr.Render();
//			glEnable(GL_DEPTH_TEST);
//		}
//
//
//		If enough time has passed, create a new generation
//		time += G.timer.GetElapsedTime();
//		if (time > trialTime)
//		{
//			Place Genetic algorithm here
//			float mutation = 0.1f;
//
//			bool changed = true;
//			while(changed)
//			{
//				shitty bubble sort
//				changed = false;
//				for(int i = 0; i< nets.size() - 1; ++i)
//				{
//					if (nets[i].score < nets[i + 1].score)
//					{
//						swap them
//						NeuralNet tempnet(nets[i]);
//						nets[i] = nets[i + 1];
//						nets[i + 1] = tempnet;
//						changed = true;
//					}
//				}
//			}
//
//			Create a top half list
//			std::vector<NeuralNet> topHalf;
//			for(int i = 0; i<nets.size()/2; ++i)
//			{
//				topHalf.push_back(nets[i]);
//			}
//			nets.clear();
//
//			TODO: SHOULD RANDOMIZE THE ORDER IN THE NEW LIST
//
//			Create children
//			int j;
//			for(int i = 0; i<topHalf.size(); ++i)
//			{
//				j = (i + 1) % topHalf.size();
//				nets.push_back(topHalf[i].Procreate(topHalf[j], mutation));
//
//				j = (i + 2) % topHalf.size();
//				nets.push_back(topHalf[i].Procreate(topHalf[j], mutation));
//			}
//
//			Reset the board
//			for (int i = 0; i < ships.size(); i++)
//			{
//				ships[i].direction = Random(0.0f, 360.0f);
//				ships[i].position.x = Random(-4.5f, 4.5f);
//				ships[i].position.y = Random(-4.5f, 4.5f);
//				nets[i].score = 0.0f;
//			}
//			for (int i = 0; i < gems.size(); i++)
//			{
//				gems[i] = vec2(Random(-4.5f, 4.5f), Random(-4.5f, 4.5f));
//			}
//
//			generation++;
//			std::string title = "Generation: ";
//			title += std::to_string(generation);
//			title += " Average Score: ";
//			title += std::to_string(averageScore / trialTime);
//			std::cout << title << std::endl;
//			G.window.setTitle(title);
//			time = 0.0f; //Reset the timer
//			score = 0.0f;
//		}
//
//	}
//	return 0;
//}
//
//
