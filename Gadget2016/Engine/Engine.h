//SFML Game Engine
//Brent Cowan 2016
#pragma once
#pragma comment(linker, "/NODEFAULTLIB:LIBC.lib")

//GLEW to manage extensions
#define GLEW_STATIC
#include "GLEW/glew.h"
#pragma comment(lib,"Engine/GLEW/glew32s.lib")

//SFML Includes
#define SFML_STATIC
#include "SFML/include/SFML/Graphics.hpp"
#include "SFML/include/SFML/OpenGL.hpp"

//SFML Libraries
#ifdef _DEBUG
#pragma comment(lib,"Engine/SFML/lib/sfml-audio-s-d.lib")
#pragma comment(lib,"Engine/SFML/lib/sfml-graphics-s-d.lib")
#pragma comment(lib,"Engine/SFML/lib/sfml-window-s-d.lib")
#pragma comment(lib,"Engine/SFML/lib/sfml-system-s-d.lib")
#else
#pragma comment(lib,"Engine/SFML/lib/sfml-audio-s.lib")
#pragma comment(lib,"Engine/SFML/lib/sfml-graphics-s.lib")
#pragma comment(lib,"Engine/SFML/lib/sfml-window-s.lib")
#pragma comment(lib,"Engine/SFML/lib/sfml-system-s.lib")
#endif

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Engine/SFML/lib/freetype.lib")
#pragma comment(lib,"Engine/SFML/lib/jpeg.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//Constants
#define PI  3.14159265f
#define DTR 0.01745329f // (PI / 180)
#define RTD 57.2957795f // (180 / PI)

//Include GLM math library
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
using namespace glm;

//Some standard Includes
#include <vector>
#include <list>

//Additional Vector Math Functions
#include "VectorMath.h"

//A simple 2D game engine
#include "Timer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera2D.h"
#include "Gadget.h"

#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"