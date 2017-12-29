#ifndef RAY_H
#define RAY_H

#include "CollisionLayers.h"
#include "Vector2.h"
#include "Rect.h"

class CollidableObject;

class Ray
{
	public:
		Ray(Vector2<float> origin, Vector2<float> direction, COLLISION_LAYERS layerMask, float distance);
		virtual ~Ray();
		Vector2<float> origin();
		Vector2<float> direction();
		COLLISION_LAYERS layerMask();
		float distance();
		float intersect(Rect<int> rect);
	private:
		float segmentIntersectRectangle(float rectangleMinX,
                                        float rectangleMinY,
                                        float rectangleMaxX,
                                        float rectangleMaxY,
                                        float p1x,
                                        float p1y,
                                        float p2x,
                                        float p2y);
		CollidableObject* _owner;
		Vector2<float> _origin;
		Vector2<float> _direction;
		COLLISION_LAYERS _layerMask;
		float _distance;
		float _p1x;
		float _p1y;
		float _p2x;
		float _p2y;
		Rect<int> _rayBounds;
};

#endif