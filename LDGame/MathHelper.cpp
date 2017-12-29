#include "MathHelper.h"
#include <stdlib.h>

const float MathHelper::PI = 3.14159265359;
const float MathHelper::DEGREE_TO_PI = PI/180;
const float MathHelper::PI_TO_DEGREE = 180/PI;

float MathHelper::distance(float p1x,float p1y,float p2x,float p2y)
{
	return sqrt( ((p2x - p1x)*(p2x - p1x)) + ((p2y - p1y)*(p2y - p1y)) );
}

float MathHelper::distance(const Vector2<float> &p1, const Vector2<float> &p2)
{
	return distance(p1.x, p1.y, p2.x, p2.y);
}

void MathHelper::normaliseVector2f(Vector2<float> &vector)
{
	float magnitude = sqrt((vector.x * vector.x) + (vector.y * vector.y));
	if(magnitude != 0)
	{
		vector.x /= magnitude;
		vector.y /= magnitude;
	}
}

float MathHelper::getDegreesFromVector(const Vector2<float> &vector)
{
	return getDegreesFromVector(vector.x, vector.y);
}

float MathHelper::getDegreesFromVector(float x, float y)
{
	return ((atan2(y, x) * PI_TO_DEGREE));
}

Vector2<float> MathHelper::getVectorFromDegrees(float degrees)
{
	return getVectorFromRadians(convertDegreesToRadians(degrees));
}

Vector2<float> MathHelper::getVectorFromRadians(float radians)
{
	return Vector2<float>(cos(radians), sin(radians));
}

float MathHelper::convertDegreesToRadians(float degrees)
{
	return degrees * DEGREE_TO_PI;
}

float MathHelper::convertRadiansToDegrees(float radians)
{
	return radians * PI_TO_DEGREE;
}

float MathHelper::lerp(float t, float a, float b)
{
	return (1-t)*a + (t*b);
}

Vector2<float> MathHelper::lerpVector2f(float t, const Vector2<float> &a, const Vector2<float> &b)
{
	return Vector2<float>( (1-t)*a.x + (t * b.x), (1-t)*a.y + (t * b.y));
}

float MathHelper::randomFloat()
{
	return ((double)rand() / (RAND_MAX));
}

float MathHelper::randomFloatInRange(float minValue, float maxValue)
{
	return minValue + (randomFloat()*(maxValue - minValue));
}