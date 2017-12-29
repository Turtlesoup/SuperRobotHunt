#include "EnemyTypeDataManager.h"
#include "StringHelper.h"
#include "Resources.h"
#include "Enemy.h"
#include "EnemyGun.h"
#include "GameScene.h"
#include "AudioManager.h"

const std::wstring ENEMY_TYPES = L"enemyTypes";

EnemyTypeDataManager *EnemyTypeDataManager::_instance = nullptr;

EnemyTypeDataManager::EnemyTypeDataManager()
{
}

EnemyTypeDataManager::~EnemyTypeDataManager()
{
}

EnemyTypeDataManager *EnemyTypeDataManager::Get()
{
	if(_instance == nullptr)
	{
		_instance = new EnemyTypeDataManager();
	}

	return _instance;
}

void EnemyTypeDataManager::init(std::vector<std::string> &resourceURLs)
{
	//load the enemy data json object
	std::wstring jsonString = StringHelper::loadFromFile(ENEMY_TYPES_DATA);
	JSONObject jsonObject = JSON::Parse(jsonString.c_str())->AsObject();

	//create the enemy type datas
	JSONArray enemyTypeDataJSONArray = jsonObject[ENEMY_TYPES]->AsArray();
	unsigned int enemyTypeDataArrayLength = enemyTypeDataJSONArray.size();
	for(unsigned int enemyTypeDataArrayIndex = 0; enemyTypeDataArrayIndex < enemyTypeDataArrayLength; ++ enemyTypeDataArrayIndex)
	{
		//create the enemy type data
		EnemyTypeData enemyTypeData = EnemyTypeData::fromJSONObject(enemyTypeDataJSONArray[enemyTypeDataArrayIndex]->AsObject());
		_enemyTypeDatas.push_back(enemyTypeData);

		//initialise the sounds in the audio manager
		AudioManager::Get()->loadSound(enemyTypeData.spawnSoundURL);
		AudioManager::Get()->loadSound(enemyTypeData.destroySoundURL);

		//if the resource url hasnt been added to the resource urls list then add it
		if(std::find(resourceURLs.begin(), resourceURLs.end(), enemyTypeData.textureURL) == resourceURLs.end())
		{
			resourceURLs.push_back(enemyTypeData.textureURL);
		}
	}
}

Enemy *EnemyTypeDataManager::createEnemy(unsigned int typeID, GameScene *gameScene, Vector2<float> position, std::vector<LOOT_TYPES> lootTypes)
{
	const EnemyTypeData &enemyTypeData = getEnemyTypeData(typeID);

	//create the gun instances
	std::vector<Gun*> guns;
	unsigned int numGuns = enemyTypeData.gunProperties.size();
	for(unsigned int gunIndex = 0; gunIndex < numGuns; ++gunIndex)
	{
		guns.push_back(new EnemyGun(enemyTypeData.gunProperties[gunIndex], *gameScene));
	}

	return new Enemy(position,
					 lootTypes,
					 *gameScene,
					 enemyTypeData.aimGunsAtPlayer,
					 guns,
					 enemyTypeData.aiData,
					 enemyTypeData.normalMovementSpeed,
					 enemyTypeData.chaseMovementSpeed,
					 enemyTypeData.detectionDistanceThreshold,
					 enemyTypeData.maxHealth,
					 enemyTypeData.destroyScore,
					 enemyTypeData.hitDelay,
					 enemyTypeData.hitForce,
					 enemyTypeData.criticalHitPowerMultiplier,
					 enemyTypeData.criticalHitPercentage,
					 enemyTypeData.textureURL,
					 TEXTURE_ATLAS_SPRITES,
					 enemyTypeData.spriteDimensions,
					 enemyTypeData.animations,
					 enemyTypeData.lightProperties,
					 gameScene->underLightLayer(),
					 enemyTypeData.spawnSoundURL,
					 enemyTypeData.destroySoundURL);
}

const std::vector<EnemyTypeData> &EnemyTypeDataManager::getEnemyTypeDatas()
{
	return _enemyTypeDatas;
}

const EnemyTypeData &EnemyTypeDataManager::getEnemyTypeData(unsigned int typeID)
{
	unsigned int enemyTypeDatasLength = _enemyTypeDatas.size();
	for(unsigned int enemyTypeDatasIndex = 0; enemyTypeDatasIndex < enemyTypeDatasLength; ++enemyTypeDatasIndex)
	{
		if(_enemyTypeDatas[enemyTypeDatasIndex].typeID == typeID)
		{
			return _enemyTypeDatas[enemyTypeDatasIndex];
		}
	}

	throw std::exception("enemy type with given type ID does not exist: " + typeID);
}