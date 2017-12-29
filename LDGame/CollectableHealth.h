#ifndef COLLECTABLE_HEALTH_H
#define COLLECTABLE_HEALTH_H

#include "Collectable.h"

class CollectableHealth : public Collectable
{
	public:
		CollectableHealth(const Vector2<float> &position, GameScene &gameScene);
		virtual ~CollectableHealth();
		virtual void onCollected(Player *player);
	private:
		const float HEALTH_VALUE;
};

#endif