#ifndef COLLECTABLE_WEAPON_H
#define COLLECTABLE_WEAPON_H

#include "Collectable.h"
#include "Player.h"

class CollectableWeapon : public Collectable
{
	public:
		CollectableWeapon(const Vector2<float> &position, GameScene &gameScene);
		virtual ~CollectableWeapon();
		virtual void onCollected(Player *player);
	private:
		GunProperties _gunProperties;
		const float HEALTH_VALUE;
};

#endif