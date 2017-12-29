#ifndef CUBIC_BEZIER_CURVE_H
#define CUBIC_BEZIER_CURVE_H

#include "Vector2.h"

class CubicBezierCurve
{
	public:
		CubicBezierCurve();
		CubicBezierCurve(Vector2<float> p1, Vector2<float> p2, Vector2<float> p3, Vector2<float> p4);
		virtual ~CubicBezierCurve();
		Vector2<float> getPoint(float interpolationValue);
		Vector2<float> &getP1();
		Vector2<float> &getP2();
		Vector2<float> &getP3();
		Vector2<float> &getP4();
	private:
		Vector2<float> _p1;
		Vector2<float> _p2;
		Vector2<float> _p3;
		Vector2<float> _p4;
};

#endif