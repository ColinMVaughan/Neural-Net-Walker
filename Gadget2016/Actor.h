#pragma once
#include "NeuralNet.h"
#include "Engine/GLM/detail/type_vec2.hpp"

class Actor
{
public:
	Actor();
	~Actor();

	Actor Procreate(Actor& other);
	NeuralNet brain;

	glm::vec2 dir;
	float fov;
};
