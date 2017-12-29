#ifndef ENEMY_GUN_H
#define ENEMY_GUN_H

#include "Gun.h"

class EnemyGun : public Gun
{
	public:
		EnemyGun(GunProperties gunProperties, GameScene &gameScene);
		virtual ~EnemyGun();
		void shoot(Vector2<float> bulletPosition, float angle);
		static bool onBulletHit(BaseBullet* bullet, float bulletXAdvance, float bulletYAdvance, CollidableObject* collidingObject);
};

#endif