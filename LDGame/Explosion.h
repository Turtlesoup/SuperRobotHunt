#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "OneShotEffect.h"
#include "GameScene.h"

class Explosion : public OneShotEffect
{
	public:
		Explosion(Vector2<float> position, GameScene& gameScene);
		virtual ~Explosion();
};

#endif