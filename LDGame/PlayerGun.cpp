#include "PlayerGun.h"
#include "BaseBullet.h"
#include "Directions.h"
#include "CollidableObject.h"
#include "Enemy.h"
#include "MathHelper.h"
#include "BulletTypeDataManager.h"

#include <functional>

PlayerGun::PlayerGun(GunProperties gunProperties, GameScene &gameScene) : Gun(gunProperties, gameScene)
{
}

PlayerGun::~PlayerGun()
{
}

void PlayerGun::shoot(Vector2<float> bulletPosition, float angle)
{
	if(_currentBulletDelay <= 0.0)
	{
		unsigned int numBullets = _gunProperties.numBullets();
		std::vector<unsigned int> bulletTypes = _gunProperties.bulletTypes();
		std::vector<float> bulletOffsets = _gunProperties.bulletOffsets();
		std::vector<float> bulletRandomSpread = _gunProperties.bulletRandomSpread();

		for(unsigned int bulletIndex = 0; bulletIndex < numBullets; ++ bulletIndex)
		{
			unsigned int bulletType = bulletTypes[bulletIndex];
			float bulletOffsetValue = bulletOffsets[bulletIndex];
			float bulletRandomSpreadValue = bulletRandomSpread[bulletIndex];

			//get the bullet direction
			float bulletAngle = angle + bulletOffsetValue + MathHelper::randomFloatInRange(-bulletRandomSpreadValue, bulletRandomSpreadValue);
			Vector2<float> shootDirection = MathHelper::getVectorFromDegrees(bulletAngle);

			BaseBullet* bullet = BulletTypeDataManager::Get()->createBullet(bulletType, _gameScene, bulletPosition, shootDirection, COLLISION_LAYERS::LAYER_3, COLLISION_LAYERS::LAYER_2);
			bullet->setBulletHitCallback( std::bind(&PlayerGun::onBulletHit, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4) );
			_gameScene.gameLayer()->addChild(bullet);
			_bullets.push_back(bullet);
			bullet->shoot();
		}

		_currentBulletDelay = _gunProperties.shotDelay();
	}
}

bool PlayerGun::onBulletHit(BaseBullet* bullet, float bulletXAdvance, float bulletYAdvance, CollidableObject* collidingObject)
{
	Enemy* enemy = dynamic_cast<Enemy*>(collidingObject);
	if(enemy != 0)
	{
		enemy->hit(bulletXAdvance, bulletYAdvance, bullet->power());
		return true;
	}
	return false;
}

