#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include "DisplayObject.h"

#include <vector>

class SpriteDisplayObject;

const unsigned int NUM_HEALTH_PARTS = 10;
const unsigned int HEALTH_BAR_SPACING = 18;

class HealthBar : public DisplayObject
{
	public:
		HealthBar(const Vector2<float> &position);
		virtual ~HealthBar();
		void setHealthPercentage(float percentage);
	private:
		SpriteDisplayObject *fullHealthParts[NUM_HEALTH_PARTS];
		SpriteDisplayObject *emptyHealthParts[NUM_HEALTH_PARTS];
};

#endif