//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.

#pragma once
#include <Box2D.h>
#include "Character.h"
#include "Engine/Engine.h"

//Class for running game. Player races against best walker character from training.
class Game
{
public:
	Game(Gadget& engine, b2World& a_world);
	void Update();	//Update physics and logic
	void Input();	//Get Player input

	void Render(Shader& shader, Sprite& sprite);

	void Load(std::string file);	//load opponent neural net
	void GameOver(bool playerWon);	//Set game over condition

	void Reset();

private:
	b2World* World;		//phisics world ptr
	Gadget* Engine;		//rendering engine ptr

	//Physics data for ground
	b2BodyDef groundBodyDef;
	b2Body* groundBody;
	b2PolygonShape groundBox;
	b2Filter filter;

	Character* Opponent;	//Oppoent Character.
	Character* Player;		//Player Character.
										
	float timer = 0.0f;
	bool GameStopped = false;
	bool PlayerWin = false;
};