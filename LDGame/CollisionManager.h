#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Rect.h"
#include "CollisionLayers.h"
#include "Ray.h"

#include <vector>

class QuadTree;
class CollidableObject;

struct RayCast
{
	CollidableObject *owner;
	Ray *ray;
	unsigned int stopAfterCollisionsCount;
};

struct RayCollidedObject
{
	CollidableObject *object;
	float rayIntersectionDistance;
};

class CollisionManager
{
	public:
		static CollisionManager *Get();
		CollisionManager();
		virtual ~CollisionManager();
		void addCollidableObject(CollidableObject* collidableObject);
		void removeCollidableObject(CollidableObject* collidableObject);
		void checkCollisions();
		void addRayCastCheck(CollidableObject* owner, Vector2<float> origin, Vector2<float> direction, COLLISION_LAYERS layerMask, float distance, unsigned int stopAfterCollisionsCount);
	private:
		void checkBoundCollisions();
		void checkRayCollisions();
		QuadTree *_rootQuad;
		std::vector<CollidableObject*> _collidableObjects;
		std::vector<CollidableObject*> _collisionCheckingObjects;
		std::vector<RayCast> _rayCasts;
		static CollisionManager *_instance;
};

#endif