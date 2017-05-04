//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.

#pragma once
#include <Box2D.h>
#include "Character.h"
#include "Engine/Engine.h"

//TODO: Get rid of this, just use a vector
#define CHARACTER_NUM 10 // Should always be even!

//Class for running the simulation. Handling characters, physics, and rendering.
class Simulation
{
public:
	Simulation(Gadget& engine, b2World& a_world);
	void Update();
	void Render(Shader& shader, Sprite& sprite);

	//Saving and loading the neural net info for characters
	void SaveState(std::string filePath);
	void LoadState(std::string filePath);

	void CheeseIt();

	//Increment generation, procreate neural nets, and reset the sim.
	void NewGeneration();
private:
	b2World* World;		//phisics world ptr
	Gadget* Engine;		//rendering engine ptr

	//Physics data for ground
	b2BodyDef groundBodyDef;
	b2Body* groundBody;
	b2PolygonShape groundBox;
	b2Filter filter;

	std::vector<Character*> character;	//collection of characters.

	//data for ticking generations
	float timer = 0.0f;
	int GenNum = 0;

};
