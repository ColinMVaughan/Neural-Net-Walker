//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.
#include "BodyNode.h"

//Constructor creates the Rigidbody and collider for the body part.
BodyNode::BodyNode(b2World& a_world, b2Vec2 a_size, b2Vec2 a_position)
{
	World = &a_world;	//Collect physics engine reference.
	Size = a_size;		//size of the collider

	//Definition for the rigidbody, position, type, etc.
	b2BodyDef def;
	def.position = a_position;
	def.type = b2_dynamicBody;
	def.fixedRotation = false;

	//Set size of rigidbody collider
	shape.SetAsBox(Size.x, Size.y);

	//Set filter data so limbs dont collide together.
	filter.categoryBits = 0x0001;
	filter.maskBits		= 0x0002;

	//Set collider settings, friction, density etc.
	b2FixtureDef fixDef;
	fixDef.shape    = &shape;
	fixDef.density  = 1.0f;
	fixDef.filter   = filter;
	fixDef.friction = 1.0f;

	//Create the rigidbody, and attach the collider
	Body = World->CreateBody(&def);
	Body->CreateFixture(&fixDef);

}

//Destructor
BodyNode::~BodyNode()
{
}

//Depricated.
void BodyNode::Update(float time, float amplitude, float friquency)
{

}

//Connects two BodyNodes together with a revolute joint. 
//Paramaters: child BodyNode, and the local point where the nodes will connect.
void BodyNode::AddJoint(BodyNode& node, b2Vec2 localPoint)
{
	//Create joint definition
	b2RevoluteJointDef jdef;
	//set what rigidbodys are being connected and the position of the joint.
	jdef.Initialize(Body, node.Body, Body->GetWorldPoint(localPoint));
	
	b2RevoluteJoint* joint;
	joint = (b2RevoluteJoint*)World->CreateJoint(&jdef);

	//Initalize motor settings
	joint->SetMaxMotorTorque(2000);
	joint->EnableMotor(true);
	joint->SetMotorSpeed(0);

	//Parent node adds joint to vector
	joints.push_back(joint);
}

//Same as Function above but user can specify an angular constraint on the joint.
//Used so you dont get horrible spider people.
void BodyNode::AddJoint(BodyNode& node, b2Vec2 localPoint, b2Vec2 anlgeConstraints)
{
	b2RevoluteJointDef jdef;
	jdef.Initialize(Body, node.Body, Body->GetWorldPoint(localPoint));

	b2RevoluteJoint* joint;
	joint = (b2RevoluteJoint*)World->CreateJoint(&jdef);

	joint->SetMaxMotorTorque(2000);
	joint->EnableMotor(true);
	joint->SetMotorSpeed(0);

	//Sets angle constraints for the joint (in Raidians).
	//joint will not be able to exceed these angles.
	joint->SetLimits(b2_pi * anlgeConstraints.x, b2_pi * anlgeConstraints.y);
	joint->EnableLimit(true);
	joints.push_back(joint);
}
