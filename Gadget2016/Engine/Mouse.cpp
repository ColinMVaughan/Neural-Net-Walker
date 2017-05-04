//Brent Cowan Jan. 2015

#include "Engine.h"

Mouse::Mouse()
{
	left = false;
	leftPrevious = false;
	right = false;
	rightPrevious = false;
}

void Mouse::Init(sf::Window* window)
{
	this->window = window;
}

void Mouse::Update()
{
	pos = vec2(sfMouse.getPosition().x-window->getPosition().x-7.0f, 
		sfMouse.getPosition().y-window->getPosition().y-29.0f);

	leftPrevious = left;
	left = sfMouse.isButtonPressed(sf::Mouse::Left);
	rightPrevious = right;
	right = sfMouse.isButtonPressed(sf::Mouse::Right);
}

bool Mouse::GetLeftRelease()
{
	return !left && leftPrevious;
}

bool Mouse::GetLeftPress()
{
	return left && !leftPrevious;
}

bool Mouse::GetLeftHold()
{
	return left;
}

bool Mouse::GetRightRelease()
{
	return !right && rightPrevious;
}

bool Mouse::GetRightPress()
{
	return right && !rightPrevious;
}

bool Mouse::GetRightHold()
{
	return right;
}

void Mouse::Reset()
{
	rightPrevious = right = false;
	leftPrevious  = left  = false;
}

vec2 Mouse::GetPosition()
{
	return pos;
}