#ifndef DIRECTIONS
#define DIRECTIONS

#include "Vector2.h"

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Directions
{
	public:
		static Vector2<float> directionToVector2f(DIRECTION direction);
		static DIRECTION valuesToDirection(float xVal, float yVal);
		static DIRECTION vector2fToDirection(const Vector2<float> direction);
};

#endif