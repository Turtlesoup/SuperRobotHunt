#include "CubicBezierCurve.h"
#include "MathHelper.h"

CubicBezierCurve::CubicBezierCurve() : _p1(Vector2<float>()),
									   _p2(Vector2<float>()),
									   _p3(Vector2<float>()),
									   _p4(Vector2<float>())
{
}

CubicBezierCurve::CubicBezierCurve(Vector2<float> p1, Vector2<float> p2, Vector2<float> p3, Vector2<float> p4) : _p1(p1),
																										 _p2(p2),
																										 _p3(p3),
																										 _p4(p4)
{
}

CubicBezierCurve::~CubicBezierCurve()
{
}

Vector2<float> CubicBezierCurve::getPoint(float interpolationValue)
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
	Vector2<float> c = MathHelper::lerpVector2f(interpolationValue, _p3, _p4);

	Vector2<float> d = MathHelper::lerpVector2f(interpolationValue, a, b);
	Vector2<float> e = MathHelper::lerpVector2f(interpolationValue, b, c);

	return MathHelper::lerpVector2f(interpolationValue, d, e);
}

Vector2<float> &CubicBezierCurve::getP1()
{
	return _p1;
}

Vector2<float> &CubicBezierCurve::getP2()
{
	return _p2;
}

Vector2<float> &CubicBezierCurve::getP3()
{
	return _p3;
}

Vector2<float> &CubicBezierCurve::getP4()
{
	return _p4;
}