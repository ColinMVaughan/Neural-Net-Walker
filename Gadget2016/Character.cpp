//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.
#include "Character.h"
#include <iostream>

//Construct the body and brain of the Walker.
Character::Character(b2World& world)
{
	//Create the limbs of the body
	Body[0] = new BodyNode(world, b2Vec2(3.0f,1.0f), b2Vec2(0.0f,0.0f));
	Body[1] = new BodyNode(world, b2Vec2(0.5f,2.0f), b2Vec2(2.0f,-2.0f));
	Body[2] = new BodyNode(world, b2Vec2(0.5f,2.0f), b2Vec2(-2.0f,-2.0f));

	//set angle constraints for the leg joints (no horrible spider people)
	b2Vec2 angleConstraints(-0.5, 0.5);

	//Connect the body parts with joints
	Body[0]->AddJoint(*Body[1], b2Vec2(2.0f,-1.0f), angleConstraints);
	Body[0]->AddJoint(*Body[2], b2Vec2(-2.0f,-1.0f), angleConstraints);

	//Create the Neural Net. Neural Net is feedforward.
	int sizes[3] = { 1 ,7, 6};
	Brain = new NeuralNet(3, sizes);

}

//Set joint rotation based on the output of the Neural Net.
void Character::Update(float time)
{
	//Get current joint angle as Input.
	//input[0] = Body[0]->joints[0]->GetJointAngle();
	input[0] = 1.0f;
	//input[1] = Body[0]->joints[1]->GetJointAngle();

	//Normailize inputs
	//input[0] = (input[0] - (-1.5)) / (1.5 - (-1.5));
	//input[1] = (input[1] - (-1.5)) / (1.5 - (-1.5));

	Brain->Update(input, output);

	//pack range into [-1,1]
	output[0] = output[0] * 2.0f - 1.0f;
	output[1] = output[1] * 2.0f - 1.0f;


	//Set the Motor speed of the joints based on Neural Net output.
	Body[0]->joints[0]->SetMotorSpeed(output[0] * sin((output[1] * 3.14) * time + output[2]));
	Body[0]->joints[1]->SetMotorSpeed(output[3] * sin((output[4] * 3.14) * time + output[5]));
}

//Create new neural net by combining two.
NeuralNet Character::Procreate(Character& other, float mutation)
{
	return Brain->Procreate(*other.Brain, mutation);
}

//Set positions and rotations back to default.
void Character::Reset()
{
	Body[0]->Body->SetTransform(b2Vec2(0.0f, 0.0f), 0);
	Body[1]->Body->SetTransform(b2Vec2(2.0f, -2.0f), 0);
	Body[2]->Body->SetTransform(b2Vec2(-2.0f, -2.0f), 0);

	Body[0]->Body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	Body[1]->Body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	Body[2]->Body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

	Body[0]->Body->SetAngularVelocity(0.0f);
	Body[1]->Body->SetAngularVelocity(0.0f);
	Body[2]->Body->SetAngularVelocity(0.0f);

}

//Delete the current net and replace it with a new one.
void Character::ReplaceNet(NeuralNet& Net)
{
	delete Brain;
	Brain = &Net;
}