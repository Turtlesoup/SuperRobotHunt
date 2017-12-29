#include "CircleFlash.h"
#include "Resources.h"
#include "FlickeringLight.h"

CircleFlash::CircleFlash(Vector2<float> position, GameScene& gameScene, bool showLight, const sf::Color &tint, float scaleFactor) : OneShotEffect(SPRITE_CIRCLE_FLASH,
																																				  TEXTURE_ATLAS_SPRITES,
																																				  position,
																																				  50,
																																				  Vector2<float>(64, 64),
																																				  sf::Color(255, 255, 255, 100),
																																				  500,
																																				  gameScene.underLightLayer(),
																																				  Vector2<float>(0, 0),
																																				  gameScene)
{
	std::vector<unsigned int> frames;
	frames.push_back(0);
	frames.push_back(1);
	frames.push_back(2);
	frames.push_back(3);
	frames.push_back(4);
	setAnimationFrames(frames);

	_light->setVisible(showLight);

	setTint(tint);
	setScale(scaleFactor, scaleFactor);
}

CircleFlash::~CircleFlash()
{
}