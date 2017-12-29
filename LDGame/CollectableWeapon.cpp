#include "CollectableWeapon.h"
#include "Resources.h"
#include "GunProperties.h"
#include "Player.h"
#include "AudioManager.h"

CollectableWeapon::CollectableWeapon(const Vector2<float> &position, GameScene &gameScene) : Collectable(position,
																										 gameScene,
																										 SPRITE_COLLECTABLE_1,
																										 Vector2<float>(15,29),
																										 9,
																										 sf::Color(255, 50, 255),
																										 200),
																							 _gunProperties(GunProperties::createRandomProperties()),
																							 HEALTH_VALUE(10)
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
	frames.push_back(7);
	addAnimation("idle", frames);
	frames.clear();

	frames.push_back(8);
	frames.push_back(9);
	frames.push_back(10);
	addAnimation("collect", frames);
	frames.clear();

	play("idle");
}

CollectableWeapon::~CollectableWeapon()
{
}

void CollectableWeapon::onCollected(Player *player)
{
	player->addHealth(HEALTH_VALUE);

	//set a random gun property
	player->setGunProperties(_gunProperties);

	_gameScene.spawnTextIndicator("Weapon Change!", _position, sf::Color(255, 255, 255), sf::Color(255, 100, 100), 20);

	//play the collected sfx
	AudioManager::Get()->playSound(AUDIO_COLLECT_WEAPON);
}