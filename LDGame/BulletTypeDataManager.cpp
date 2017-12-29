#include "BulletTypeDataManager.h"
#include "StringHelper.h"
#include "Resources.h"
#include "Enemy.h"
#include "EnemyGun.h"
#include "GameScene.h"
#include "BaseBullet.h"
#include "OmniDirectionBullet.h"
#include "CurveBullet.h"
#include "LaserBullet.h"
#include "Resources.h"
#include "MathHelper.h"
#include "AudioManager.h"

const std::wstring BULLET_TYPES = L"bulletTypes";

BulletTypeDataManager *BulletTypeDataManager::_instance = nullptr;

BulletTypeDataManager::BulletTypeDataManager()
{
}

BulletTypeDataManager::~BulletTypeDataManager()
{
}

BulletTypeDataManager *BulletTypeDataManager::Get()
{
	if(_instance == nullptr)
	{
		_instance = new BulletTypeDataManager();
	}

	return _instance;
}

void BulletTypeDataManager::init(std::vector<std::string> &resourceURLs)
{
	//load the bullet data json object
	std::wstring jsonString = StringHelper::loadFromFile(BULLET_TYPES_DATA);
	JSONObject jsonObject = JSON::Parse(jsonString.c_str())->AsObject();

	//create the bullet type datas
	JSONArray bulletTypeDataJSONArray = jsonObject[BULLET_TYPES]->AsArray();
	unsigned int bulletTypeDataArrayLength = bulletTypeDataJSONArray.size();
	for(unsigned int bulletTypeDataArrayIndex = 0; bulletTypeDataArrayIndex < bulletTypeDataArrayLength; ++ bulletTypeDataArrayIndex)
	{
		//create tthe bullet type
		BulletTypeData bulletTypeData = BulletTypeData::fromJSONObject(bulletTypeDataJSONArray[bulletTypeDataArrayIndex]->AsObject());
		_bulletTypeDatas.push_back(bulletTypeData);

		//initialise the sounds in the audio manager
		AudioManager::Get()->loadSound(bulletTypeData.shootSoundURL);
		AudioManager::Get()->loadSound(bulletTypeData.destroySoundURL);

		//if the resource url hasnt been added to the resource urls list then add it
		std::vector<std::string> textureURLs = bulletTypeData.textureURLs;
		for(std::vector<std::string>::iterator textureURLIter = textureURLs.begin(); textureURLIter != textureURLs.end(); ++textureURLIter)
		{
			std::string textureURL = (*textureURLIter);
			if(std::find(resourceURLs.begin(), resourceURLs.end(), textureURL) == resourceURLs.end())
			{
				resourceURLs.push_back(textureURL);
			}
		}
	}
}

BaseBullet *BulletTypeDataManager::createBullet(unsigned int typeID, GameScene &gameScene, Vector2<float> bulletPosition, Vector2<float> shootDirection, COLLISION_LAYERS collisionLayer, COLLISION_LAYERS collisionCheckingLayer)
{
	const BulletTypeData &bulletTypeData = getBulletTypeData(typeID);
	switch(bulletTypeData.behaviourTypeID)
	{
	case BULLET_BEHAVIOUR_TYPE_OMNIDIRECTIONAL:
		{
			OmniDirectionBullet *omniDirectionBullet = new OmniDirectionBullet(gameScene,
																			   collisionLayer,
																			   bulletTypeData.textureURLs[0],
																			   TEXTURE_ATLAS_SPRITES,
																			   bulletPosition,
																			   shootDirection.x,
																			   shootDirection.y,
																			   bulletTypeData.speed,
																			   bulletTypeData.lifetime,
																			   bulletTypeData.bounceOffWalls,
																			   bulletTypeData.power,
																			   bulletTypeData.collisionSize,
																			   bulletTypeData.animationSpeed,
																			   bulletTypeData.spriteDimensions,
																			   bulletTypeData.lightProperties.colour,
																			   bulletTypeData.lightProperties.size,
																			   gameScene.underLightLayer(),
																			   bulletTypeData.lightProperties.offset,
																			   bulletTypeData.animations,
																			   bulletTypeData.shootSoundURL,
																			   bulletTypeData.destroySoundURL);
			omniDirectionBullet->setCollisionLayer(collisionLayer);
			omniDirectionBullet->setCollisionCheckingLayer(collisionCheckingLayer);
			omniDirectionBullet->setCollisionChecking(true);
			omniDirectionBullet->setDoRayCastCheckOnBulletTravelPath(bulletTypeData.doRayCastCheckOnBulletTravelPath);
			return omniDirectionBullet;
		}
		break;
	case BULLET_BEHAVIOUR_TYPE_CURVE:
		{
			CurveBullet *curveBullet = new CurveBullet(gameScene,
														collisionLayer,
														bulletTypeData.textureURLs[0],
														TEXTURE_ATLAS_SPRITES,
														bulletPosition,
														shootDirection.x,
														shootDirection.y,
														bulletTypeData.speed,
														bulletTypeData.lifetime,
														bulletTypeData.bounceOffWalls,
														bulletTypeData.power,
														bulletTypeData.collisionSize,
														bulletTypeData.animationSpeed,
														bulletTypeData.spriteDimensions,
														bulletTypeData.lightProperties.colour,
														bulletTypeData.lightProperties.size,
														gameScene.underLightLayer(),
														bulletTypeData.lightProperties.offset,
														bulletTypeData.amplitude,
														bulletTypeData.frequency,
														bulletTypeData.animations,
														bulletTypeData.shootSoundURL,
														bulletTypeData.destroySoundURL);
			curveBullet->setCollisionLayer(collisionLayer);
			curveBullet->setCollisionCheckingLayer(collisionCheckingLayer);
			curveBullet->setCollisionChecking(true);
			curveBullet->setDoRayCastCheckOnBulletTravelPath(bulletTypeData.doRayCastCheckOnBulletTravelPath);
			return curveBullet;
		}
		break;
	case BULLET_BEHAVIOUR_TYPE_RAY:
		{
			LaserBullet *lasterBullet = new LaserBullet(gameScene,
													    collisionCheckingLayer,
													    bulletTypeData.textureURLs[0],
														bulletTypeData.textureURLs[1],
														bulletTypeData.textureURLs[2],
													    TEXTURE_ATLAS_SPRITES,
													    bulletPosition,
													    shootDirection.x,
													    shootDirection.y,
													    bulletTypeData.speed,
														bulletTypeData.lifetime,
													    bulletTypeData.power,
													    bulletTypeData.collisionSize,
														bulletTypeData.animationSpeed,
													    bulletTypeData.spriteDimensions,
													    bulletTypeData.lightProperties.colour,
													    bulletTypeData.lightProperties.size,
													    gameScene.underLightLayer(),
													    bulletTypeData.lightProperties.offset,
													    bulletTypeData.animations,
														bulletTypeData.shootSoundURL,
														bulletTypeData.destroySoundURL);
			lasterBullet->setCollisionChecking(false);
			return lasterBullet;
		}
		break;
	}
}

const BulletTypeData &BulletTypeDataManager::getBulletTypeData(unsigned int typeID)
{
	unsigned int bulletTypeDatasLength = _bulletTypeDatas.size();
	for(unsigned int bulletTypeDatasIndex = 0; bulletTypeDatasIndex < bulletTypeDatasLength; ++bulletTypeDatasIndex)
	{
		if(_bulletTypeDatas[bulletTypeDatasIndex].typeID == typeID)
		{
			return _bulletTypeDatas[bulletTypeDatasIndex];
		}
	}

	throw std::exception("bullet type with given type ID does not exist: " + typeID);
}

unsigned int BulletTypeDataManager::getRandomBulletTypeID(bool playerBullet)
{
	unsigned int bulletTypeDatasLength = _bulletTypeDatas.size();
	unsigned int startIndex = unsigned int(MathHelper::randomFloatInRange(0, bulletTypeDatasLength));
	unsigned int endIndex = 0;
	if(startIndex == 0)
	{
		endIndex = bulletTypeDatasLength;
	}
	else
	{
		endIndex = startIndex - 1;
	}

	for(unsigned int bulletTypeDatasIndex = startIndex; bulletTypeDatasIndex != endIndex; ++bulletTypeDatasIndex)
	{
		if(bulletTypeDatasIndex == bulletTypeDatasLength)
		{
			bulletTypeDatasIndex = 0;
		}
		if(_bulletTypeDatas[bulletTypeDatasIndex].playerBullet == playerBullet)
		{
			return _bulletTypeDatas[bulletTypeDatasIndex].typeID;
		}
	}
}