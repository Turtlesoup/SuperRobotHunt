#include "WaveManager.h"
#include "StringHelper.h"
#include "Resources.h"
#include "MathHelper.h"
#include "EnemyTypeDataManager.h"
#include <cassert>

WaveManager *WaveManager::_instance = nullptr;

WaveManager::WaveManager()
{
}

WaveManager::~WaveManager()
{
}

WaveManager *WaveManager::Get()
{
	if(_instance == nullptr)
	{
		_instance = new WaveManager();
	}

	return _instance;
}

void WaveManager::init()
{
	//load the wave data json object
	std::wstring jsonString = StringHelper::loadFromFile(WAVE_DATA);
	JSONObject jsonObject = JSON::Parse(jsonString.c_str())->AsObject();

	//read spawn patterns list
	JSONArray spawnPatternsDataJSONArray = jsonObject[L"spawnPatterns"]->AsArray();
	unsigned int spawnPatternsDataArrayLength = spawnPatternsDataJSONArray.size();
	for(unsigned int spawnPatternsDataArrayIndex = 0; spawnPatternsDataArrayIndex < spawnPatternsDataArrayLength; ++ spawnPatternsDataArrayIndex)
	{
		_spawnPatterns.push_back(SpawnPatternData::fromJSONObject(spawnPatternsDataJSONArray[spawnPatternsDataArrayIndex]->AsObject()));
	}
}

std::vector<EnemyData> WaveManager::createWaveDataSet(unsigned int waveNumber)
{
	SpawnPatternData spawnPattern;

	if(waveNumber != 0 && waveNumber % 10 == 0)
	{
		//spawn a loot wave every 10 waves
		spawnPattern = _spawnPatterns[0];
	}
	else
	{
		//select a random wave layout
		unsigned int randomIndex = unsigned int(MathHelper::randomFloatInRange(1, _spawnPatterns.size()));
		spawnPattern = _spawnPatterns[randomIndex];
	}

	//determine if weapon of health loot will appear in this wave, and if so, select a random enemy index to asign the loot to
	bool spawnWeapon = MathHelper::randomFloatInRange(0, 1) <= spawnPattern.lootWeaponChance;
	bool spawnLife = MathHelper::randomFloatInRange(0, 1) <= spawnPattern.lootWeaponChance;
	int weaponEnemyIndex = -1;
	int lifeEnemyIndex = -1;
	if(spawnWeapon)
	{
		weaponEnemyIndex = int(MathHelper::randomFloatInRange(0, spawnPattern.numEnemies));
	}
	if(spawnLife)
	{
		lifeEnemyIndex = int(MathHelper::randomFloatInRange(0, spawnPattern.numEnemies));
	}

	//get the list of all valid enemy types based on the current wave number as a measurement of how difficult the wave should be
	unsigned int maxEnemyDifficulty = ((float)waveNumber / 5.0f) + 2;
	std::vector<unsigned int> validEnemyTypeIDs;
	std::vector<EnemyData> enemyDatas;
	std::vector<EnemyTypeData> enemyTypeDatas = EnemyTypeDataManager::Get()->getEnemyTypeDatas();
	for(std::vector<EnemyTypeData>::iterator enemyTypeDatasIter = enemyTypeDatas.begin(), enemyTypeDatasEnd = enemyTypeDatas.end(); enemyTypeDatasIter != enemyTypeDatasEnd; ++enemyTypeDatasIter)
	{
		if((*enemyTypeDatasIter).difficulty <= maxEnemyDifficulty)
		{
			validEnemyTypeIDs.push_back((*enemyTypeDatasIter).typeID);
		}
	}
	assert(validEnemyTypeIDs.size());

	//for each group, select a random valid enemy type and create the enemies
	std::vector<std::vector<Vector2<float>>> spawnGroups = spawnPattern.groups;
	unsigned int groupLength = spawnGroups.size();
	unsigned int enemyIndex = 0;
	for(unsigned int groupIndex = 0; groupIndex < groupLength; ++groupIndex)
	{
		std::vector<Vector2<float>> spawnPositions = spawnGroups[groupIndex];
		
		//select a random enemy type for the group
		unsigned int groupEnemyTypeID = validEnemyTypeIDs[unsigned int(MathHelper::randomFloatInRange(0, validEnemyTypeIDs.size()))];

		//create the enemies at the spawn positions
		unsigned int spawnPositionsLength = spawnPositions.size();
		for(unsigned int spawnPositionsIndex = 0; spawnPositionsIndex < spawnPositionsLength; ++spawnPositionsIndex)
		{
			EnemyData enemyData;
			enemyData.enemyType = groupEnemyTypeID;
			enemyData.spawnPosition = spawnPositions[spawnPositionsIndex];

			if(spawnWeapon || spawnLife)
			{
				if(enemyIndex == weaponEnemyIndex)
				{
					enemyData.loot.push_back(WEAPON);
				}
				if(enemyIndex == lifeEnemyIndex)
				{
					enemyData.loot.push_back(HEALTH);
				}
			}

			enemyDatas.push_back(enemyData);

			//increase enemy count
			++enemyIndex;
		}
	}

	return enemyDatas;
}