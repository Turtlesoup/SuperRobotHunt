#include "Gun.h"
#include "BaseBullet.h"
#include "Directions.h"
#include "CollidableObject.h"

#include <functional>

Gun::Gun(GunProperties gunProperties, GameScene &gameScene) : GameObject(),
															  _gunProperties(gunProperties),
															  _currentBulletDelay(0),
															  _gameScene(gameScene)
{
}

Gun::~Gun()
{
}

void Gun::update(float deltaTime)
{
	//decrease bullet delay
	if(_currentBulletDelay > 0.0)
	{
		_currentBulletDelay -= deltaTime;
	}
}

void Gun::onRemoved()
{
	//if we are destroying the gun then we must also destroy any bullets that are not currently being fired
	std::vector<BaseBullet*>::iterator bulletsIterator, bulletsBegin, bulletsEnd;
	bulletsBegin = _bullets.begin();
	bulletsEnd = _bullets.end();
	BaseBullet *bullet;
	for(bulletsIterator = bulletsBegin; bulletsIterator != bulletsEnd; ++ bulletsIterator)
	{
		bullet = (*bulletsIterator);
		if(bullet->isDead())
		{
			//remove the bullet if the bullet is currently dead
			_gameScene.removeChild(bullet, true);
		}
		else
		{
			//if the bullet is not dead then set the reuse bullet flag to false
			//this means that the bullet will dispose itself when it collides
			bullet->setReuseBullet(false);
		}
	}

	//clear the bullets list
	_bullets.clear();
}

void Gun::setProperties(GunProperties gunProperties)
{
	_gunProperties = gunProperties;
}