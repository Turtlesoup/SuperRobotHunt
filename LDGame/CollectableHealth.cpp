#include "CollectableHealth.h"
#include "Resources.h"
#include "ScoreValues.h"
#include "Player.h"
#include "AudioManager.h"

CollectableHealth::CollectableHealth(const Vector2<float> &position, GameScene &gameScene) : Collectable(position,
																							 gameScene,
																							 SPRITE_COLLECTABLE_4,
																							 Vector2<float>(15,29),
																							 9,
																							 sf::Color(255, 255, 255),
																							 200),
																							 HEALTH_VALUE(2)
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

CollectableHealth::~CollectableHealth()
{
}

void CollectableHealth::onCollected(Player *player)
{
	player->addHealth(HEALTH_VALUE);

	_gameScene.spawnTextIndicator("Health Up!", _position, sf::Color(255, 255, 255), sf::Color(100, 255, 100), 20);

	//play the collected sfx
	AudioManager::Get()->playSound(AUDIO_COLLECT_HEALTH);
}