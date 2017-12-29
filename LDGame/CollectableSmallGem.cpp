#include "CollectableSmallGem.h"
#include "Resources.h"
#include "ScoreValues.h"
#include "Player.h"
#include "AudioManager.h"
#include <string>

CollectableSmallGem::CollectableSmallGem(const Vector2<float> &position, GameScene &gameScene) : Collectable(position,
																								 gameScene,
																								 SPRITE_COLLECTABLE_3,
																								 Vector2<float>(7,17),
																								 9,
																								 sf::Color(255, 100, 100),
																								 50)
{
	//create animations
	std::vector<unsigned int> frames;

	frames.push_back(0);
	frames.push_back(1);
	frames.push_back(2);
	frames.push_back(3);
	frames.push_back(4);
	frames.push_back(5);
	frames.push_back(6);
	addAnimation("idle", frames);
	frames.clear();

	frames.push_back(7);
	frames.push_back(8);
	frames.push_back(9);
	addAnimation("collect", frames);
	frames.clear();

	play("idle");
}

CollectableSmallGem::~CollectableSmallGem()
{
}

void CollectableSmallGem::onCollected(Player *player)
{
	_gameScene.increaseScore(SMALL_GEM_SCORE);

	_gameScene.spawnTextIndicator("+" + std::to_string((long long)SMALL_GEM_SCORE), _position, sf::Color(255, 255, 255), sf::Color(255, 194, 14), 20);

	//play the collected sfx
	AudioManager::Get()->playSound(AUDIO_COLLECT_SMALL_GEM);
}