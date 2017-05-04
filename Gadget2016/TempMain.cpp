//#include <Box2D.h>
//#include "Engine/Engine.h"
//
//enum collideCatagory
//{
//	col1 = 0x0001,
//	col2 = 0x0002
//};
//
//
//int main()
//{
//	b2World World(b2Vec2(0.0f,-10.0f));
//
//	b2BodyDef bodyDef2;
//	b2Body* body2;
//	b2PolygonShape groundBox;
//	b2Filter filter1;
//	b2Filter filter2;
//
//	filter1.categoryBits = col1;
//	filter1.maskBits = col2;
//
//	filter2.categoryBits = col2;
//	filter2.maskBits = col1;
//
//
//	//Create body 2
//	bodyDef2.position.Set(0.0f, 2.0f);
//	body2 = World.CreateBody(&bodyDef2);
//	groundBox.SetAsBox(1.0f, 1.0f);
//	
//	body2->CreateFixture(&groundBox, 0.0f)->SetFilterData(filter1);
//	
//	//Create body 1
//	b2BodyDef bodyDef;
//	bodyDef.type = b2_dynamicBody;
//	bodyDef.position.Set(0.0f, 9.0f);
//	b2Body* body = World.CreateBody(&bodyDef);
//
//	b2PolygonShape dynamicBox;
//	dynamicBox.SetAsBox(1.0f, 1.0f);
//
//	b2FixtureDef fixtureDef;
//	fixtureDef.shape = &dynamicBox;
//	fixtureDef.density = 1.0f;
//	fixtureDef.friction = 0.3f;
//
//	body->CreateFixture(&fixtureDef)->SetFilterData(filter1);
//
//
//
//
//	//Create Joint
//	b2RevoluteJointDef jointDef;
//	//jointDef.Initialize(body, body2->GetWorldCenter());
//
//	//jointDef.lowerAngle = -0.5f * b2_pi; // -90 degrees
//	//jointDef.upperAngle = 0.25f * b2_pi; // 45 degrees
//	//jointDef.enableLimit = true;
//	jointDef.maxMotorTorque = 10.0f;
//	jointDef.motorSpeed = 0.0f;
//	jointDef.enableMotor = true;
//
//	b2RevoluteJoint* joint = (b2RevoluteJoint*)World.CreateJoint(&jointDef);
//
//
//	float timestamp = 1.0f / 60.0f;
//	int velocityIterations = 6;
//	int positionIterations = 2;
//
//
//
////////////////////////////////////////////////////////////////////////////
//	Gadget G; G.OpenWindow(600, 600, false, false, false);
//	G.window.setMouseCursorVisible(false); //hide mouse curser
//	G.camera.SetZoom(50.0f); //Screen is 10 units wide
//
//	Shader shade; shade.Load("Shaders/SpriteVert.glsl", "Shaders/SpriteFrag.glsl");
//
//	//Mario texture and sprite
//	Texture marioTex; marioTex.Load("Resources/MarioTiles.png");
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	Sprite marioSpr; marioSpr.SetScale(vec2(1.2f, 1.4f));
//
//
//	while (G.Update()) // Start the game loop
//	{
//		World.Step(timestamp, velocityIterations, positionIterations);
//		//joint->SetMotorSpeed(100.5f);
//		b2Vec2 position = body->GetPosition();
//		float rotation = body->GetAngle();
//
//		b2Vec2 position2 = body2->GetPosition();
//		float rotation2 = body2->GetAngle();
//
//
//		vec2 pos;
//		pos.x = position.x;
//		pos.y = position.y;
//
//		vec2 pos2;
//		pos2.x = position2.x;
//		pos2.y = position2.y;
//
//		shade.Activate();
//		shade.Blend(1);
//		shade.SetMat4("MVP", G.camera.GetProjection() * marioSpr.GetMatrix());
//		shade.SetVec4("spriteUV", marioSpr.GetUVs());
//		shade.SetImage(marioTex.GetID(), "myTextureSampler", 0);
//
//
//		//Render dynamic body 2
//		marioSpr.SetFrame(16, 16, 64, 64, 6, false);
//		marioSpr.SetPosition(vec3(pos2, 1.0f));
//		marioSpr.SetScale(vec2(1.0f, 1.0f));
//		marioSpr.SetRotation(rotation2);
//
//		marioSpr.Render();
//
//
//		shade.SetMat4("MVP", G.camera.GetProjection() * marioSpr.GetMatrix());
//		shade.SetVec4("spriteUV", marioSpr.GetUVs());
//		shade.SetImage(marioTex.GetID(), "myTextureSampler", 0);
//
//		//Render Dynamic body 1
//		marioSpr.SetFrame(16, 16, 64, 64, 0, false);
//		marioSpr.SetPosition(vec3(pos,1.0f));
//		marioSpr.SetScale(vec2(1.0f, 1.0f));
//		marioSpr.SetRotation(rotation);
//
//		marioSpr.Render();
//	}
//
//
//	return 0;
//}
