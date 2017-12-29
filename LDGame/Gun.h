#ifndef GUN_H
#define GUN_H

#include "GameScene.h"
#include "GameObject.h"
#include "GunProperties.h"

class BaseBullet;
class CollidableObject;

class Gun : public GameObject
{
	public:
		Gun(GunProperties gunProperties, GameScene &gameScene);
		virtual ~Gun();
		void update(float deltaTime);
		virtual void shoot(Vector2<float> bulletPosition, float angle) = 0;
		void onRemoved();
		void setProperties(GunProperties gunProperties);
	protected:
		GameScene &_gameScene;
		std::vector<BaseBullet*> _bullets;
		GunProperties _gunProperties;
		float _currentBulletDelay;
};

#endif