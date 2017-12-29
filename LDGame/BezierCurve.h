#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include "Vector2.h"

class BezierCurve
{
	public:
		BezierCurve();
		BezierCurve(Vector2<float> p1, Vector2<float> p2, Vector2<float> p3);
		virtual ~BezierCurve();
		Vector2<float> getPoint(float interpolationValue);
		Vector2<float> &getP1();
		Vector2<float> &getP2();
		Vector2<float> &getP3();
	private:
		Vector2<float> _p1;
		Vector2<float> _p2;
		Vector2<float> _p3;
};

#endif