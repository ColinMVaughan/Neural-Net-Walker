// Brent Cowan 2016
#include "Engine.h"

float Random(float min, float max)
{
	return (float(rand()) / float(RAND_MAX)) * (max - min) + min;
}

float CoinToss(float heads, float tails)
{
	if (rand() % 2) return heads;
	else return tails;
}

float Clamp(float x, float min, float max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

vec2 Rotate(const vec2 &v, float angle)
{
	static vec2 outVec;
	float rad = angle*DTR;
	float tempX = cos(rad)*v.x - sin(rad)*v.y;
	outVec.y = sin(rad)*v.x + cos(rad)*v.y;
	outVec.x = tempX;
	return outVec;
}

float Dot(const vec2 &v1, const vec2 &v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Length(const vec2 &v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

float LengthSq(const vec2 &v)
{
	return (v.x * v.x + v.y * v.y);
}

vec2 Normalize(const vec2 &v)
{
	static vec2 outVec;
	outVec = v;
	float len = sqrt(v.x * v.x + v.y * v.y);

	if (len <= 0.00001f)
	{
		outVec = AngleToVector(float(rand()%360));
	}
	else
	{
		len = 1.0f / len;
		outVec.x *= len; outVec.y *= len;
	}
	return outVec;
}

vec2 AngleToVector(float angle)
{
	return vec2(cos(angle*DTR), sin(angle*DTR));
}

float VectorToAngle(const vec2 &v)
{
	return atan2(v.y, v.x)*RTD;
}

vec2 Perp(const vec2 &v)
{
	return vec2(-v.y, v.x);
}

vec2 Reflect(const vec2 &v, const vec2 &norm)
{
	static vec2 outVec;
	outVec = v;
	outVec += (norm*-1.0f) * (Dot(outVec, norm)*2.0f);
	return outVec;
}

vec2 SetLength(const vec2 &v, float length)
{
	static vec2 outVec;
	outVec = Normalize(v);
	outVec.x *= length;
	outVec.y *= length;
	return outVec;
}

float RotateToward(float currentDir, float desiredDir, float rotationSpeed)
{
	static int tempDir; //temporarly hold the direction faced
	static float difference;

	difference = currentDir - desiredDir;

	//Decide which direction to rotate
	tempDir = int(difference) % 360;

	difference += float(int(difference / 360.0f))*-360.0f;
	if (difference<0){ difference += 360; }
	if (difference>180.0f){ difference = 360.0f - difference; }

	if (tempDir<0){ tempDir += 360; }

	if (tempDir>180)//Must be turning left
	{
		if (difference>rotationSpeed)//Don't turn more that the rotationSpeed
		{
			currentDir += rotationSpeed;
		}
		else
		{
			currentDir += difference;
		}
	}
	else //Must be turning right
	{
		if (difference>rotationSpeed)//Don't turn more that the rotationSpeed
		{
			currentDir -= rotationSpeed;
		}
		else
		{
			currentDir -= difference;
		}
	}

	currentDir += float(int(currentDir / 360.0f))*-360.0f;
	if (currentDir<0){ currentDir += 360; }

	return currentDir;
}