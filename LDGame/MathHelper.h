#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include "Vector2.h"
#include <cmath>
#include <vector>

class MathHelper
{
	public:
		static float distance(float p1x,float p1y,float p2x,float p2y);
		static float distance(const Vector2<float> &p1, const Vector2<float> &p2);
		static void normaliseVector2f(Vector2<float> &vector);
		static float getDegreesFromVector(const Vector2<float> &vector);
		static float getDegreesFromVector(float x, float y);
		static Vector2<float> getVectorFromDegrees(float degrees);
		static Vector2<float> getVectorFromRadians(float radians);
		static float convertDegreesToRadians(float degrees);
		static float convertRadiansToDegrees(float radians);
		static float lerp(float t, float a, float b);
		static Vector2<float> lerpVector2f(float t, const Vector2<float> &a, const Vector2<float> &b);
		static float randomFloat();
		static float randomFloatInRange(float minValue, float maxValue);
		static const float PI;
		static const float DEGREE_TO_PI;
		static const float PI_TO_DEGREE;

		template<typename T>
		static bool isNaN(T value)
		{
			return !(value == value);
		}
};

#endif