#ifndef COLLECTABLE_SMALL_GEM_H
#define COLLECTABLE_SMALL_GEM_H

#include "Collectable.h"

class CollectableSmallGem : public Collectable
{
	public:
		CollectableSmallGem(const Vector2<float> &position, GameScene &gameScene);
		virtual ~CollectableSmallGem();
		virtual void onCollected(Player *player);
};

#endif