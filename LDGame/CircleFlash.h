#ifndef CIRCLE_FLASH_H
#define CIRCLE_FLASH_H

#include "OneShotEffect.h"

class CircleFlash : public OneShotEffect
{
	public:
		CircleFlash(Vector2<float> position, GameScene& gameScene, bool showLight, const sf::Color &tint, float scaleFactor = 1.0f);
		virtual ~CircleFlash();
};

#endif