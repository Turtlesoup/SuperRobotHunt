#ifndef BASE_BLOCK_H
#define BASE_BLOCK_H

#include "EmittingObject.h"
#include "CollidableObject.h"
#include "GameScene.h"
#include "Vector2.h"

class Ray;

class BaseBlock : public EmittingObject, public CollidableObject
{
	public:
		BaseBlock(const Vector2<float>& position, GameScene& gameScene);
		virtual ~BaseBlock();
		virtual void update(float deltaTime);
		virtual void onCollision(CollidableObject* collidingObject);
		virtual void onRayCollision(CollidableObject* collidingObject, Ray *ray, float rayIntersectionDistance);
	private:
		GameScene& _gameScene;
};

#endif