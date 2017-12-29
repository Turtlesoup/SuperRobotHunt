#include "BezierCurve.h"
#include "MathHelper.h"

BezierCurve::BezierCurve() : _p1(Vector2<float>()),
							 _p2(Vector2<float>()),
							 _p3(Vector2<float>())
{
}

BezierCurve::BezierCurve(Vector2<float> p1, Vector2<float> p2, Vector2<float> p3) : _p1(p1),
																			  _p2(p2),
																			  _p3(p3)
{
}

BezierCurve::~BezierCurve()
{
}

Vector2<float> BezierCurve::getPoint(float interpolationValue)
{
	if(interpolationValue < 0)
	{
		interpolationValue = 0;
	}
	else if(interpolationValue > 1)
	{
		interpolationValue = 1;
	}

	Vector2<float> a = MathHelper::lerpVector2f(interpolationValue, _p1, _p2);
	Vector2<float> b = MathHelper::lerpVector2f(interpolationValue, _p2, _p3);

	return MathHelper::lerpVector2f(interpolationValue, a, b);
}

Vector2<float> &BezierCurve::getP1()
{
	return _p1;
}

Vector2<float> &BezierCurve::getP2()
{
	return _p2;
}

Vector2<float> &BezierCurve::getP3()
{
	return _p3;
}