//Brent Cowan 2016

#include "Engine.h"

mat4 Camera2D::projection;

Camera2D::Camera2D()
{
	aspectRatio = 1.333f;
	position = vec2(0.0f);
	zoom = 10.0f;
	rotation = 0.0f;
}

void Camera2D::Init(sf::Window* window)
{
	this->window = window;
}

void Camera2D::Activate()
{
	aspectRatio = float(window->getSize().x) / float(window->getSize().y);

	//Calculate the Projection matrix
	projection = mat4(1.0f);
	projection = scale(projection, vec3(2.0f / zoom, 2.0f / (zoom / aspectRatio), 2.0f/200.0f));
	projection = rotate(projection, -rotation*DTR, vec3(0.0f, 0.0f, 1.0f));
	projection = translate(projection, vec3(-position.x, -position.y, 0.0f));
}

vec3 Camera2D::ScreenToCameraCoordinates(vec2 pos)
{
	//Scale
	pos = pos / float(window->getSize().x);
	pos.x = pos.x - 0.5f;
	pos.y = -pos.y + 0.5f / aspectRatio;
	pos = pos*zoom;
	
	//Rotate
	mat4 matrix = mat4(1.0f);
	matrix = rotate(matrix, rotation*DTR, vec3(0.0f, 0.0f, 1.0f));
	vec4 screenPos = vec4(pos.x, pos.y, 0.0f, 1.0f);
	screenPos = matrix * screenPos;

	//Translate
	screenPos.x += position.x;
	screenPos.y += position.y;

	return vec3(screenPos.x, screenPos.y, 0.0f);
}

mat4 Camera2D::GetProjection() { return projection; }

vec2 Camera2D::GetPosition() { return position; }

void Camera2D::SetPosition(vec2 position) { this->position = position; }

float Camera2D::GetRotation() { return rotation; }
void Camera2D::SetRotation(float rotation) { this->rotation = rotation; }

float Camera2D::GetZoom() { return zoom; }
void Camera2D::SetZoom(float zoom) { this->zoom = zoom; }