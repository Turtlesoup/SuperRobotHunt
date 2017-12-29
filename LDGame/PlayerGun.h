#ifndef PLAYER_GUN_H
#define PLAYER_GUN_H

#include "Gun.h"

class PlayerGun : public Gun
{
	public:
		PlayerGun(GunProperties gunProperties, GameScene &gameScene);
		virtual ~PlayerGun();
		void shoot(Vector2<float> bulletPosition, float angle);
		static bool onBulletHit(BaseBullet* bullet, float bulletXAdvance, float bulletYAdvance, CollidableObject* collidingObject);
};

#endif