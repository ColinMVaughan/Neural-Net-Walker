#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>
#include "Engine.h"

Shader::Shader()
{
	init = false;
}

Shader::~Shader()
{
	if (init)
	{
		glDeleteProgram(ID);
	}
}

bool Shader::Load(const char * vertex_file_path,const char * fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return false;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	ID = ProgramID;
	init = true;

	return true;
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Deactivate()
{
	glUseProgram(0);

	glDisable(GL_BLEND);

	glActiveTexture(GL_TEXTURE0); glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1); glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2); glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE3); glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE4); glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
}

void Shader::SetImage(GLuint imageID, char* name, int imageNum)
{
	glEnable(GL_TEXTURE);
	glActiveTexture(GL_TEXTURE0 + imageNum);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, imageID);
	GLint textureID = glGetUniformLocation(ID, name);
	glUniform1i(textureID, imageNum);
}

void Shader::SetFloat(char* name, float value)
{
	GLint floatID = glGetUniformLocation(ID, name);
	glUniform1f(floatID, value);
}

void Shader::SetVec4(char* name, float x, float y, float z, float w)
{
	GLint vecID = glGetUniformLocation(ID, name);
	glUniform4f(vecID, x, y, z, w);
}

void Shader::SetVec4(char* name, vec4 vec)
{
	GLint vecID = glGetUniformLocation(ID, name);
	glUniform4f(vecID, vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetMat4(char* name, mat4 matrix)
{
	GLint matID = glGetUniformLocation(ID, name);
	glUniformMatrix4fv(matID, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::Blend(int RenderMode)
{
	glEnable(GL_BLEND);

	//Transparency Mode
	if (RenderMode == 0)      //Opaque – no transparency
	{
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}
	else if (RenderMode == 1) //Threshold – all or nothing transparency
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.5f);
		glDisable(GL_BLEND);
	}
	else if (RenderMode == 2) //Blend – Normally
	{
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else if (RenderMode == 3)       //Blend - Additively
	{
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}
	else if (RenderMode == 4)       //Blend - Subtractive
	{
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glBlendEquationEXT(GL_FUNC_REVERSE_SUBTRACT);//GL_FUNC_REVERSE_SUBTRACT
	}
	else      //Out of range! defualt to Opaque – no transparency
	{
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}
}