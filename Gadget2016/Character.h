//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.

#pragma once
#include <Box2D.h>
#include "NeuralNet.h"
#include "BodyNode.h"

#define BODY_NUM 3

//Collision layers for physics sim. power of 2 for possible bitwise ops.
enum ColissionLayers{Layer1 = 0x0001, Layer2 = 0x0002};

//Class representing the walking characters in the simulation.
//Characters learn to walk based on Neural Network & Genetic learning algorithm
class Character
{
public:

	Character(b2World& world);
	void Update(float time);

	//combine neural nets
	NeuralNet Procreate(Character& other, float mutation); 

	//change pointer to neural net
	void ReplaceNet(NeuralNet& Net);	
	//reset position and orientation of character
	void Reset();					

	b2RevoluteJoint* joint1;
	b2RevoluteJoint* joint2;

	BodyNode* Body[BODY_NUM];	//Limbs for character
	float score;		//score for how far the character walked
	NeuralNet *Brain;	//Neural net for the walker.
private:

	b2PolygonShape shapes;
	b2PolygonShape shapes2;
	b2World* world;			//pointer to the physics world
	b2Filter filter;


	float output[6];	//outputs for the neural net
	float input[1];		//Inputs for the neural net

};