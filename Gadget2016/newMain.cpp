//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.

#include <Box2D.h>
#include "Engine/Engine.h"
#include "Simulation.h"
#include <iostream>
#include "Game.h"

int main()
{
	//get level choice.
	int choice = 0;

	do
	{
		std::string file;
		std::cout << "Plese Select an Option.\n";
		std::cout << "1.Training,\t2.Play\n";

		std::cin >> choice;
	} while (choice != 1 && choice != 2 && choice != 3);

	std::cout << "\n Loading...";

	//Set up Render enging and window
	Gadget G; G.OpenWindow(1000, 600, false, false, true);
	G.window.setMouseCursorVisible(false); //hide mouse curser
	G.window.setTitle("Generation: 0 ");
	G.camera.SetZoom(30.0f); //Screen is 10 units wide
	
	//Load Shader
	Shader shade; shade.Load("Shaders/SpriteVert.glsl", "Shaders/SpriteFrag.glsl");
	
	//Load texture and sprite
	Texture Tex; Tex.Load("Resources/AI_Sprite_Sheet.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	Sprite Spr; Spr.SetScale(vec2(1.2f, 1.4f));
	
	//Initalize physics engine & Simulation.
	b2World world(b2Vec2(0.0f, -10.0f));
	Game game(G, world);
	game.Load("PlayData/TestFile.txt");

	Simulation sim(G, world);



	while (G.Update()) // Start the game loop
	{
		//Bind Shaders & textures
		shade.Activate();
		shade.Blend(1);
		shade.SetImage(Tex.GetID(), "myTextureSampler", 0);

		//Update simulation & render
		if(choice == 2)
		{
			game.Update();
			game.Render(shade, Spr);
		}
		else
		{
			sim.Update();
			sim.Render(shade, Spr);
		}


	}

	return 0;
}
