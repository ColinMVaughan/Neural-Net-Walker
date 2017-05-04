//Brent Cowan 2016

#include "Engine.h"

bool    Sprite::init = false;
GLuint  Sprite::vertexArrayID;
GLuint  Sprite::vertexBufferID;
GLuint  Sprite::uvBufferID;
GLfloat Sprite::vertexBuffer[12];
GLfloat Sprite::uvBuffer[8];

Sprite::Sprite()
{
	rotation = 0.0f;
	position = vec3(0.0f, 0.0f, 0.0f);
	scale    = vec2(1.0f, 1.0f);
	minUV = vec2(0.0f, 0.0f);
	maxUV = vec2(1.0f, 1.0f);

	if (!init)
	{
		//The vertex buffer is an array of 4 vertices
		vertexBuffer[0] = -0.5f; vertexBuffer[1]  =  0.5f; vertexBuffer[2]  = 0.0f;
		vertexBuffer[3] =  0.5f; vertexBuffer[4]  =  0.5f; vertexBuffer[5]  = 0.0f;
		vertexBuffer[6] =  0.5f; vertexBuffer[7]  = -0.5f; vertexBuffer[8]  = 0.0f;
		vertexBuffer[9] = -0.5f; vertexBuffer[10] = -0.5f; vertexBuffer[11] = 0.0f;
		
		//The UV buffer is an array of 4 texture coordinates
		uvBuffer[0] = 0.0f; uvBuffer[1] = 0.0f;
		uvBuffer[2] = 1.0f; uvBuffer[3] = 0.0f;
		uvBuffer[4] = 1.0f; uvBuffer[5] = 1.0f;
		uvBuffer[6] = 0.0f; uvBuffer[7] = 1.0f;
		
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

		glGenBuffers(1, &uvBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvBuffer), uvBuffer, GL_STATIC_DRAW);

		init = true;
	}
}

void Sprite::CleanUp()
{
	//Release the buffers
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &uvBufferID);
}

void Sprite::Render()
{
	//Vertex attribute buffer
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	//UV attribute buffer
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	//Draw the quad
	glDrawArrays(GL_QUADS, 0, 4);

	//Disable the attribute buffers
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

mat4 Sprite::GetMatrix()
{
	matrix = mat4(1.0f);
	matrix = translate(matrix, position);
	matrix = rotate(matrix, rotation*DTR, vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::scale(matrix, vec3(scale.x, scale.y, 0.0f));

	return matrix;
}

vec3 Sprite::GetPosition() { return position; }
void Sprite::SetPosition(vec3 position) { this->position = position; }

float Sprite::GetRotation() { return rotation; }
void Sprite::SetRotation(float rotation) { this->rotation = rotation; }

vec2 Sprite::GetScale() { return scale; }
void Sprite::SetScale(vec2 scale) { this->scale = scale; }

vec4 Sprite::GetUVs()
{
	return vec4(minUV.x, minUV.y, maxUV.x, maxUV.y);
}

void Sprite::SetFrame(int frameWidth, int frameHeight, int imageWidth, int imageHeight, int frame, bool flipHorizontal)
{
	int columns = imageWidth / frameWidth;
	int column = frame%columns;
	int row = frame / columns;

	minUV.x = float(column*frameWidth) / float(imageWidth);
	minUV.y = float(row*frameHeight) / float(imageHeight);
	maxUV.x = float(column*frameWidth + frameWidth) / float(imageWidth);
	maxUV.y = float(row*frameHeight + frameHeight) / float(imageHeight);

	if (flipHorizontal)
	{
		float temp = minUV.x;
		minUV.x = maxUV.x;
		maxUV.x = temp;
	}
}

void Sprite::SetTextureCoords(float minU, float maxU, float minV, float maxV)
{
	minUV.x = minU;
	minUV.y = minV;
	maxUV.x = maxU;
	maxUV.y = maxV;
}