#ifndef ENEMY_TYPE_DATA_H
#define ENEMY_TYPE_DATA_H

#include <vector>
#include <map>
#include <string>
#include "JSON.h"
#include "Vector2.h"
#include "LootTypes.h"
#include "GunProperties.h"
#include "Light.h"
#include "BaseAI.h"
#include "ChaseAI.h"
#include "ChaseExplodeAI.h"
#include "MovePathAI.h"
#include "StringHelper.h"

class Enemy;
class GameScene;

struct EnemyTypeData
{
	public:
		static EnemyTypeData fromJSONObject(JSONObject jsonObject)
		{
			EnemyTypeData enemyTypeData;

			//parse enemy data
			enemyTypeData.typeID = unsigned int(jsonObject[L"typeID"]->AsNumber());
			enemyTypeData.difficulty = unsigned int(jsonObject[L"difficulty"]->AsNumber());
			enemyTypeData.maxHealth = float(jsonObject[L"maxHealth"]->AsNumber());
			enemyTypeData.destroyScore = unsigned int(jsonObject[L"destroyScore"]->AsNumber());
			enemyTypeData.detectionDistanceThreshold = float(jsonObject[L"detectionDistanceThreshold"]->AsNumber());
			enemyTypeData.normalMovementSpeed = float(jsonObject[L"normalMovementSpeed"]->AsNumber());
			enemyTypeData.chaseMovementSpeed = float(jsonObject[L"chaseMovementSpeed"]->AsNumber());
			enemyTypeData.hitForce = float(jsonObject[L"hitForce"]->AsNumber());
			enemyTypeData.hitDelay = float(jsonObject[L"hitDelay"]->AsNumber());
			enemyTypeData.criticalHitPercentage = float(jsonObject[L"criticalHitPercentage"]->AsNumber());
			enemyTypeData.criticalHitPowerMultiplier = float(jsonObject[L"criticalHitPowerMultiplier"]->AsNumber());

			//Audio
			JSONObject audioJSONObject = jsonObject[L"audio"]->AsObject();
			enemyTypeData.spawnSoundURL = StringHelper::wideStringToString(audioJSONObject[L"spawnSound"]->AsString());
			enemyTypeData.destroySoundURL = StringHelper::wideStringToString(audioJSONObject[L"destroySound"]->AsString());

			//AI
			JSONObject aiJSONObject = jsonObject[L"ai"]->AsObject();
			unsigned int aiTypeID = unsigned int(aiJSONObject[L"aiTypeID"]->AsNumber());
			switch(aiTypeID)
			{
				case AI_TYPE_NONE:
					enemyTypeData.aiData = new BaseAIData(aiTypeID);
					break;
				case AI_TYPE_CHASE:
					{
						float movementDurationBeforeCheckDelay = float(aiJSONObject[L"movementDurationBeforeCheckDelay"]->AsNumber());
						float checkLocationDelayTime = float(aiJSONObject[L"checkLocationDelayTime"]->AsNumber());
						bool onlyFollowWhenDetected = aiJSONObject[L"onlyFollowWhenDetected"]->AsBool();
						float movePathDirectionX = float(aiJSONObject[L"directionX"]->AsNumber());
						float movePathDirectionY = float(aiJSONObject[L"directionY"]->AsNumber());
						enemyTypeData.aiData = new ChaseAIData(aiTypeID, movementDurationBeforeCheckDelay, checkLocationDelayTime, onlyFollowWhenDetected, movePathDirectionX, movePathDirectionY);
					}
					break;
				case AI_TYPE_CHASE_EXPLODE:
					{
						float movementDurationBeforeCheckDelay = float(aiJSONObject[L"movementDurationBeforeCheckDelay"]->AsNumber());
						float checkLocationDelayTime = float(aiJSONObject[L"checkLocationDelayTime"]->AsNumber());
						bool onlyFollowWhenDetected = aiJSONObject[L"onlyFollowWhenDetected"]->AsBool();
						float movePathDirectionX = float(aiJSONObject[L"directionX"]->AsNumber());
						float movePathDirectionY = float(aiJSONObject[L"directionY"]->AsNumber());
						float explodeDelayTime = float(aiJSONObject[L"explodeDelayTime"]->AsNumber());
						float explodeHitRadius = float(aiJSONObject[L"explodeHitRadius"]->AsNumber());
						float explodeHitForce = float(aiJSONObject[L"explodeHitForce"]->AsNumber());
						enemyTypeData.aiData = new ChaseExplodeAIData(aiTypeID, movementDurationBeforeCheckDelay, checkLocationDelayTime, onlyFollowWhenDetected, movePathDirectionX, movePathDirectionY, explodeDelayTime, explodeHitRadius, explodeHitForce);
					}
					break;
				case AI_TYPE_MOVE_PATH:
					{
						float movePathDirectionX = float(aiJSONObject[L"directionX"]->AsNumber());
						float movePathDirectionY = float(aiJSONObject[L"directionY"]->AsNumber());
						enemyTypeData.aiData = new MovePathAIData(aiTypeID, movePathDirectionX, movePathDirectionY);
					}
					break;
			}

			//Aiming
			if(jsonObject.find(L"aimGunsAtPlayer") != jsonObject.end())
			{
				enemyTypeData.aimGunsAtPlayer = jsonObject[L"aimGunsAtPlayer"]->AsBool();
			}
			else
			{
				enemyTypeData.aimGunsAtPlayer = false;
			}

			//Guns
			JSONArray gunsJSONArray = jsonObject[L"guns"]->AsArray();
			unsigned int gunsArrayLength = gunsJSONArray.size();
			for(unsigned int gunsArrayIndex = 0; gunsArrayIndex < gunsArrayLength; ++ gunsArrayIndex)
			{
				JSONObject gunJSONObject = gunsJSONArray[gunsArrayIndex]->AsObject();
				float shotDelay = float(gunJSONObject[L"shotDelay"]->AsNumber());

				unsigned int numBullets = unsigned int(gunJSONObject[L"numBullets"]->AsNumber());

				JSONArray bulletTypesJSONArray = gunJSONObject[L"bulletTypes"]->AsArray();
				JSONArray bulletOffsetsJSONArray = gunJSONObject[L"bulletOffsets"]->AsArray();
				JSONArray bulletRandomSpreadJSONArray = gunJSONObject[L"bulletRandomSpread"]->AsArray();

				std::vector<unsigned int> bulletTypes;
				std::vector<float> bulletOffsets;
				std::vector<float> bulletRandomSpreads;

				for(unsigned int bulletIndex = 0; bulletIndex < numBullets; ++bulletIndex)
				{
					bulletTypes.push_back(unsigned int(bulletTypesJSONArray[bulletIndex]->AsNumber()));
					bulletOffsets.push_back(float(bulletOffsetsJSONArray[bulletIndex]->AsNumber()));
					bulletRandomSpreads.push_back(float(bulletRandomSpreadJSONArray[bulletIndex]->AsNumber()));
				}

				GunProperties gunProperties(shotDelay, bulletTypes, bulletOffsets, bulletRandomSpreads);
				enemyTypeData.gunProperties.push_back(gunProperties);
			}

			//Light
			JSONObject lightJSONObject = jsonObject[L"light"]->AsObject();
			enemyTypeData.lightProperties.size = lightJSONObject[L"size"]->AsNumber();
			JSONObject lightColourJSONObject = lightJSONObject[L"colour"]->AsObject();
			enemyTypeData.lightProperties.colour.r = unsigned int(lightColourJSONObject[L"red"]->AsNumber());
			enemyTypeData.lightProperties.colour.g = unsigned int(lightColourJSONObject[L"green"]->AsNumber());
			enemyTypeData.lightProperties.colour.b = unsigned int(lightColourJSONObject[L"blue"]->AsNumber());
			enemyTypeData.lightProperties.colour.a = unsigned int(lightColourJSONObject[L"alpha"]->AsNumber());
			JSONObject lightOffsetJSONObject = lightJSONObject[L"offset"]->AsObject();
			enemyTypeData.lightProperties.offset.x = float(lightOffsetJSONObject[L"x"]->AsNumber());
			enemyTypeData.lightProperties.offset.y = float(lightOffsetJSONObject[L"y"]->AsNumber());

			//Animations
			enemyTypeData.textureURL = StringHelper::wideStringToString(jsonObject[L"textureURL"]->AsString());
			JSONObject spriteDimensionsJSONObject = jsonObject[L"spriteDimensions"]->AsObject();
			enemyTypeData.spriteDimensions.x = float(spriteDimensionsJSONObject[L"width"]->AsNumber());
			enemyTypeData.spriteDimensions.y = float(spriteDimensionsJSONObject[L"height"]->AsNumber());
			JSONArray animationsJSONArray = jsonObject[L"animations"]->AsArray();
			unsigned int animationsJSONArrayLength = animationsJSONArray.size();
			for(unsigned int animationsJSONArrayIndex = 0; animationsJSONArrayIndex < animationsJSONArrayLength; ++animationsJSONArrayIndex)
			{
				JSONObject animationJSONObject = animationsJSONArray[animationsJSONArrayIndex]->AsObject();

				std::string animationID = StringHelper::wideStringToString(animationJSONObject[L"id"]->AsString());

				std::vector<unsigned int> frames;
				JSONArray framesJSONArray = animationJSONObject[L"frames"]->AsArray();
				unsigned int framesJSONArrayLength = framesJSONArray.size();
				for(unsigned int framesJSONArrayIndex = 0; framesJSONArrayIndex < framesJSONArrayLength; ++framesJSONArrayIndex)
				{
					frames.push_back(unsigned int(framesJSONArray[framesJSONArrayIndex]->AsNumber()));
				}

				enemyTypeData.animations[animationID] = frames;
			}


			//return the enemy data
			return enemyTypeData;
		}
		virtual ~EnemyTypeData()
		{
		}

		unsigned int typeID;
		unsigned int difficulty;
		float maxHealth;
		unsigned int destroyScore;
		float detectionDistanceThreshold;
		float normalMovementSpeed;
		float chaseMovementSpeed;
		float hitForce;
		float hitDelay;
		float criticalHitPercentage;
		float criticalHitPowerMultiplier;
		bool aimGunsAtPlayer;
		std::vector<GunProperties> gunProperties;
		BaseAIData *aiData;
		LightProperties lightProperties;
		std::string textureURL;
		Vector2<float> spriteDimensions;
		std::map<std::string, std::vector<unsigned int>> animations;
		std::string spawnSoundURL;
		std::string destroySoundURL;

	private:
		EnemyTypeData()
		{
		}
};

class EnemyTypeDataManager
{
	public:
		EnemyTypeDataManager();
		virtual ~EnemyTypeDataManager();
		static EnemyTypeDataManager *Get();
		void init(std::vector<std::string> &resourceURLs);
		Enemy *createEnemy(unsigned int typeID, GameScene *gameScene, Vector2<float> position, std::vector<LOOT_TYPES> lootTypes);
		const std::vector<EnemyTypeData> &getEnemyTypeDatas();
	private:
		static EnemyTypeDataManager *_instance;
		const EnemyTypeData &getEnemyTypeData(unsigned int typeID);
		std::vector<EnemyTypeData> _enemyTypeDatas;
};

#endif