#include "Ray.h"
#include "MathHelper.h"

#include <numeric>

Ray::Ray(Vector2<float> origin, Vector2<float> direction, COLLISION_LAYERS layerMask, float distance) : _origin(origin),
																										_direction(direction),
																										_layerMask(layerMask),
																										_distance(distance)
{
	float left;
	float right;
	float top;
	float bottom;

	_p1x = origin.x;
	_p1y = origin.y;
	_p2x = origin.x + (direction.x * distance);
	_p2y = origin.y + (direction.y * distance);

	if(direction.x < 0)
	{
		left = _p2x;
		right = _p1x;
	}
	else
	{
		left = _p1x;
		right = _p2x;
	}

	if(direction.y < 0)
	{
		top = _p2y;
		bottom = _p1y;
	}
	else
	{
		top = _p1y;
		bottom = _p2y;
	}

	_rayBounds.left = left;
	_rayBounds.width = right - left + 1;
	
	_rayBounds.top = top;
	_rayBounds.height = bottom - top + 1;
}

Ray::~Ray()
{
}

Vector2<float> Ray::origin()
{
	return _origin;
}

Vector2<float> Ray::direction()
{
	return _direction;
}

COLLISION_LAYERS Ray::layerMask()
{
	return _layerMask;
}

float Ray::distance()
{
	return _distance;
}

float Ray::intersect(Rect<int> rect)
{
	//if the ray bounding box doesnt intersect the rectangle then we can return false
	if(_rayBounds.intersects(rect))
	{
		return segmentIntersectRectangle(rect.left,
										 rect.top,
										 rect.left + rect.width,
										 rect.top + rect.height,
										 _p1x,
										 _p1y,
										 _p2x,
										 _p2y);
	}
	else
	{
		return FLT_MAX;
	}
}

float Ray::segmentIntersectRectangle(float rectangleMinX,
                                     float rectangleMinY,
                                     float rectangleMaxX,
                                     float rectangleMaxY,
                                     float p1x,
                                     float p1y,
                                     float p2x,
                                     float p2y)
{
	//find min and max X for the segment
	float minX = p1x;
	float maxX = p2x;

	if(p1x > p2x)
	{
		minX = p2x;
		maxX = p1x;
	}

	//find the intersection of the segment's and rectangle's x-projections
	if(maxX > rectangleMaxX)
	{
		maxX = rectangleMaxX;
	}

	if(minX < rectangleMinX)
	{
		minX = rectangleMinX;
	}

	//if their projections do not intersect return false
	if(minX > maxX)
	{
		return FLT_MAX;
	}

	//find corresponding min and max Y for min and max X we found before
	float minY = p1y;
	float maxY = p2y;

	float dx = p2x - p1x;

	if(abs(dx) > 0.01)
	{
		float a = (p2y - p1y) / dx;
		float b = p1y - a * p1x;
		minY = a * minX + b;
		maxY = a * maxX + b;
	}

	if(minY > maxY)
	{
		float tmp = maxY;
		maxY = minY;
		minY = tmp;
	}

	//find the intersection of the segment's and rectangle's y-projections
	if(maxY > rectangleMaxY)
	{
		maxY = rectangleMaxY;
	}

	if(minY < rectangleMinY)
	{
		minY = rectangleMinY;
	}

	//if Y-projections do not intersect return false
	if(minY > maxY)
	{
		return FLT_MAX;
	}

	//given minX, maxX, minY, maxY, compute the point closest to the origin
	float intersectionX;
	float intersectionY;
	if(p1x < minX)
	{
		intersectionX = minX;
	}
	else
	{
		intersectionX = maxX;
	}

	if(p1y < minY)
	{
		intersectionY = minY;
	}
	else
	{
		intersectionY = maxY;
	}

	return MathHelper::distance(p1x, p1y, intersectionX, intersectionY);
}