#include "Explosion.h"
#include "Resources.h"

Explosion::Explosion(Vector2<float> position, GameScene& gameScene) : OneShotEffect(SPRITE_EXPLOSION,
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
	frames.push_back(5);
	frames.push_back(6);
	setAnimationFrames(frames);
}

Explosion::~Explosion()
{
}