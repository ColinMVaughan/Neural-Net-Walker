// Brent Cowan 2016
//Additional 2D vector math functions (gml seems to be lacking)

#ifndef _VectorMath_
#define _VectorMath_

float Random(float min, float max);

float CoinToss(float heads, float tails);

float Clamp(float x, float min, float max);

vec2 Rotate(const vec2 &v, float angle);

float Dot(const vec2 &v1, const vec2 &v2);

float Length(const vec2 &v);

float LengthSq(const vec2 &v);

vec2 Normalize(const vec2 &v);

vec2 AngleToVector(float angle);

float VectorToAngle(const vec2 &v);

vec2 Perp(const vec2 &v);

vec2 Reflect(const vec2 &v, const vec2 &norm);

vec2 SetLength(const vec2 &v, float length);

float RotateToward(float currentDir, float desiredDir, float rotationSpeed);

#endif