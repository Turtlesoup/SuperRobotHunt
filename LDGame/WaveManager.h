#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include <vector>
#include "JSON.h"
#include "Vector2.h"
#include "LootTypes.h"

struct EnemyData
{
	unsigned int enemyType;
	Vector2<float> spawnPosition;
	std::vector<LOOT_TYPES> loot;
};

struct SpawnPatternData
{
	static SpawnPatternData fromJSONObject(JSONObject jsonObject)
	{
		SpawnPatternData spawnPatternData;

		spawnPatternData.numEnemies = 0;

		//read the spawn groups data
		JSONArray groupsJSONArray = jsonObject[L"groups"]->AsArray();
		unsigned int groupsArrayLength = groupsJSONArray.size();
		for(unsigned int groupsArrayIndex = 0; groupsArrayIndex < groupsArrayLength; ++ groupsArrayIndex)
		{
			JSONObject spawnPositionsJSONObject = groupsJSONArray[groupsArrayIndex]->AsObject();

			//read the spawn positions data
			std::vector<Vector2<float>> positions;
			JSONArray positionsJSONArray = spawnPositionsJSONObject[L"spawnPositions"]->AsArray();
			unsigned int positionsArrayLength = positionsJSONArray.size();
			for(unsigned int positionsArrayIndex = 0; positionsArrayIndex < positionsArrayLength; ++ positionsArrayIndex)
			{
				JSONObject spawnPos = positionsJSONArray[positionsArrayIndex]->AsObject();
				positions.push_back(Vector2<float>(spawnPos[L"x"]->AsNumber(),spawnPos[L"y"]->AsNumber()));
			}

			//increase enemy count
			spawnPatternData.numEnemies += positions.size();

			spawnPatternData.groups.push_back(positions);
		}

		spawnPatternData.lootWeaponChance = jsonObject[L"lootWeaponChance"]->AsNumber();
		spawnPatternData.lootLifeChance = jsonObject[L"lootLifeChance"]->AsNumber();

		//return the enemy group
		return spawnPatternData;
	}
	std::vector<std::vector<Vector2<float>>> groups;
	float lootWeaponChance;
	float lootLifeChance;
	unsigned int numEnemies;
};

class WaveManager
{
	public:
		WaveManager();
		virtual ~WaveManager();
		void init();
		static WaveManager *Get();
		std::vector<EnemyData> createWaveDataSet(unsigned int waveNumber);
	private:
		static WaveManager *_instance;
		std::vector<SpawnPatternData> _spawnPatterns;
};

#endif