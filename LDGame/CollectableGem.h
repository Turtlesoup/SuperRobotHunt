#ifndef COLLECTABLE_GEM_H
#define COLLECTABLE_GEM_H

#include "Collectable.h"

class CollectableGem : public Collectable
{
	public:
		CollectableGem(const Vector2<float> &position, GameScene &gameScene);
		virtual ~CollectableGem();
		virtual void onCollected(Player *player);
};

#endif