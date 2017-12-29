#ifndef COLLIDABLE_OBJECT_H
#define COLLIDABLE_OBJECT_H

#include "Rect.h"
#include "GameObject.h"
#include "CollisionLayers.h"

class Ray;

class CollidableObject : public virtual GameObject
{
	public:
		CollidableObject(COLLISION_LAYERS collisionLayer = COLLISION_LAYERS::LAYER_1, COLLISION_LAYERS collisionCheckingLayer = COLLISION_LAYERS::LAYER_1);
		virtual ~CollidableObject();
		Rect<int> &getCollisionBounds();
		void setCollisionBounds(const Rect<int> &collisionBounds);
		bool getCollidable();
		void setCollidable(bool collidable);
		bool getCollisionChecking();
		void setCollisionChecking(bool collisionChecking);
		int getCollisionBoundsLeft();
		int getCollisionBoundsTop();
		int getCollisionBoundsWidth();
		int getCollisionBoundsHeight();
		void setCollisionBoundsLeft(int value);
		void setCollisionBoundsTop(int value);
		void setCollisionBoundsWidth(int value);
		void setCollisionBoundsHeight(int value);
		COLLISION_LAYERS getCollisionLayer();
		void setCollisionLayer(COLLISION_LAYERS collisionLayer);
		COLLISION_LAYERS getCollisionCheckingLayer();
		void setCollisionCheckingLayer(COLLISION_LAYERS collisionCheckingLayer);
		virtual void onCollision(CollidableObject *collidingObject) = 0;
		virtual void onRayCollision(CollidableObject *collidingObject, Ray *ray, float rayIntersectionDistance) = 0;
	private:
		Rect<int> _collisionBounds;
		bool _collidable;
		bool _collisionChecking;
		COLLISION_LAYERS _collisionLayer;
		COLLISION_LAYERS _collisionCheckingLayer;
};

#endif