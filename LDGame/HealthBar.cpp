#include "HealthBar.h"
#include "Resources.h"
#include "SpriteDisplayObject.h"

#include <cmath>

HealthBar::HealthBar(const Vector2<float> &position) : DisplayObject(position)
{
	for(unsigned int healthPartIndex = 0; healthPartIndex < NUM_HEALTH_PARTS; ++ healthPartIndex)
	{
		fullHealthParts[healthPartIndex] = new SpriteDisplayObject(SPRITE_HEALTH_BAR_SEGMENT, TEXTURE_ATLAS_SPRITES, Vector2<float>(healthPartIndex*HEALTH_BAR_SPACING, 0));
		addChild(fullHealthParts[healthPartIndex]);

		emptyHealthParts[healthPartIndex] = new SpriteDisplayObject(SPRITE_HEALTH_BAR_SEGMENT_EMPTY, TEXTURE_ATLAS_SPRITES, Vector2<float>(healthPartIndex*HEALTH_BAR_SPACING, 0));
		emptyHealthParts[healthPartIndex]->setVisible(false);
		addChild(emptyHealthParts[healthPartIndex]);
	}
}

HealthBar::~HealthBar()
{
}

void HealthBar::setHealthPercentage(float percentage)
{
	unsigned int numBarsToShow = ceil(percentage * NUM_HEALTH_PARTS);
	for(unsigned int healthPartIndex = 0; healthPartIndex < NUM_HEALTH_PARTS; ++ healthPartIndex)
	{
		fullHealthParts[healthPartIndex]->setVisible(healthPartIndex < numBarsToShow);
		emptyHealthParts[healthPartIndex]->setVisible(healthPartIndex >= numBarsToShow);
	}
}