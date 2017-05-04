//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.

#pragma once
#include <Box2D.h>
#include <list>
#include <vector>

//BodyNode represents the a limb (or torso etc.) of a character. 
//Holds all the nessisary physics data to be connected to other body parts
class BodyNode
{
public:
	//Each body node needs a pointer to the physics world, a size, and a starting position.
	BodyNode(b2World& a_world, b2Vec2 a_size, b2Vec2 a_position);
	~BodyNode();

	//NOT CURRENTLY NEEDED!!!
	void Update(float time, float amplitude, float frequency);

	//Connects two BodyNodes together with a joint.
	void AddJoint(BodyNode& node, b2Vec2 localPoint);
	void AddJoint(BodyNode& node, b2Vec2 localPoint, b2Vec2 anlgeConstraints);

	float A, F; //No idea...

	b2Vec2 Size; //Holds size of limb for scaling sprite.

	b2Body* Body;			//Pointer to the rigidbody
	b2World* World;			//pointer to the physics world.
	b2Filter filter;		//collision filter so body parts dont collide with eachother
	b2PolygonShape shape;	//shape of limb4

	std::list<BodyNode> children;			//list of other BodyNodes connected to it. NOT NEEDED I DONT THINK!!!
	std::vector<b2RevoluteJoint*> joints;	//vector of joints connecting to other BodyNodes
};
