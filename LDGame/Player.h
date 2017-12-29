#ifndef PLAYER_H
#define PLAYER_H

#include "EmittingObject.h"
#include "CollidableObject.h"
#include "Directions.h"
#include "GameScene.h"
#include "GunProperties.h"

class SceneLayer;
class PlayerGun;
class Scene;

class Player : public EmittingObject, public CollidableObject
{
	public:
		Player(const Vector2<float>& position, GameScene& gameScene);
		virtual ~Player();
		void update(float deltaTime);
		void onCollision(CollidableObject* collidingObject);
		void onRayCollision(CollidableObject* collidingObject, Ray *ray, float rayIntersectionDistance);
		void moveUp(float deltaTime);
		void moveDown(float deltaTime);
		void moveLeft(float deltaTime);
		void moveRight(float deltaTime);
		void shoot(float deltaTime);
		void hit(float xDirection, float yDirection, float power);
		void destroy();
		void onAdded(SceneLayer *sceneLayer, GameObject *parent);
		void onRemoved(bool deletingObject);
		void addHealth(float value);
		float currentHealthPercentage();
		bool isDead();
		void setGunProperties(GunProperties gunProperties);
	private:
		GameScene& _gameScene;
		PlayerGun *_gun;
		const float MAX_HEALTH;
		float _health;
		bool _dead;
		std::string _currentAnimation;
		float _currentVelocityX;
		float _currentVelocityY;
		DIRECTION _currentDirection;
		const float ACCELERATION;
		const float DECELERATION;
		const float MAX_SPEED;
		const int BULLET_OFFSET_X_LEFT;
		const int BULLET_OFFSET_X_RIGHT;
		const int BULLET_OFFSET_X_UP;
		const int BULLET_OFFSET_X_DOWN;
		const int BULLET_OFFSET_Y_LEFT;
		const int BULLET_OFFSET_Y_RIGHT;
		const int BULLET_OFFSET_Y_UP;
		const int BULLET_OFFSET_Y_DOWN;

		const float HIT_DELAY;
		float _currentHitDelay;
		DIRECTION _hitDirection;
		const float HIT_FORCE;
};

#endif