#include "Directions.h"
#include <cmath>

Vector2<float> Directions::directionToVector2f(DIRECTION direction)
{
	switch(direction)
	{
		case DIRECTION::UP:
			return Vector2<float>(0, -1);
			break;
		case DIRECTION::DOWN:
			return Vector2<float>(0, 1);
			break;
		case DIRECTION::LEFT:
			return Vector2<float>(-1, 0);
			break;
		case DIRECTION::RIGHT:
			return Vector2<float>(1, 0);
			break;
		default:
			return Vector2<float>(0, 0);
	}
}

DIRECTION Directions::valuesToDirection(float xVal, float yVal)
{
	if(abs(xVal) >= abs(yVal))
	{
		if(xVal >= 0)
		{
			return DIRECTION::RIGHT;
		}
		else
		{
			return DIRECTION::LEFT;
		}
	}
	else
	{
		if(yVal >= 0)
		{
			return DIRECTION::DOWN;
		}
		else
		{
			return DIRECTION::UP;
		}
	}
}

DIRECTION Directions::vector2fToDirection(const Vector2<float> direction)
{
	return valuesToDirection(direction.x, direction.y);
}