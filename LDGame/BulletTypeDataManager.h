#ifndef BULLET_TYPE_DATA_MANAGER_H
#define BULLET_TYPE_DATA_MANAGER_H

#include "JSON.h"
#include "StringHelper.h"
#include "Vector2.h"
#include "Light.h"

#include <vector>
#include <map>
#include <string>

class BaseBullet;
class GameScene;

enum BULLET_BEHAVIOUR_TYPE
{
	BULLET_BEHAVIOUR_TYPE_OMNIDIRECTIONAL,
	BULLET_BEHAVIOUR_TYPE_CURVE,
	BULLET_BEHAVIOUR_TYPE_RAY
};

struct BulletTypeData
{
	public:
		static BulletTypeData fromJSONObject(JSONObject jsonObject)
		{
			BulletTypeData bulletTypeData;

			//parse enemy data
			bulletTypeData.typeID = unsigned int(jsonObject[L"typeID"]->AsNumber());
			bulletTypeData.playerBullet = jsonObject[L"playerBullet"]->AsBool();
			bulletTypeData.power = float(jsonObject[L"power"]->AsNumber());
			bulletTypeData.speed = float(jsonObject[L"speed"]->AsNumber());
			bulletTypeData.lifetime = float(jsonObject[L"lifetime"]->AsNumber());
			bulletTypeData.bounceOffWalls = jsonObject[L"bounceOffWalls"]->AsBool();
			bulletTypeData.collisionSize = float(jsonObject[L"collisionSize"]->AsNumber());
			bulletTypeData.doRayCastCheckOnBulletTravelPath = jsonObject[L"doRayCastCheckOnBulletTravelPath"]->AsBool();
			bulletTypeData.minPerShot = unsigned int(jsonObject[L"minPerShot"]->AsNumber());
			bulletTypeData.maxPerShot = unsigned int(jsonObject[L"maxPerShot"]->AsNumber());
			bulletTypeData.minBulletSpread = unsigned int(jsonObject[L"minBulletSpread"]->AsNumber());
			bulletTypeData.maxBulletSpread = unsigned int(jsonObject[L"maxBulletSpread"]->AsNumber());
			bulletTypeData.minBulletAccuracyOffset = unsigned int(jsonObject[L"minBulletAccuracyOffset"]->AsNumber());
			bulletTypeData.maxBulletAccuracyOffset = unsigned int(jsonObject[L"maxBulletAccuracyOffset"]->AsNumber());

			//Audio
			JSONObject audioJSONObject = jsonObject[L"audio"]->AsObject();
			bulletTypeData.shootSoundURL = StringHelper::wideStringToString(audioJSONObject[L"shootSound"]->AsString());
			bulletTypeData.destroySoundURL = StringHelper::wideStringToString(audioJSONObject[L"destroySound"]->AsString());

			//Bullet Behaviour
			JSONObject behaviourJSONObject = jsonObject[L"behaviour"]->AsObject();
			bulletTypeData.behaviourTypeID = static_cast<BULLET_BEHAVIOUR_TYPE>(unsigned int(behaviourJSONObject[L"behaviourTypeID"]->AsNumber()));
			switch(bulletTypeData.behaviourTypeID)
			{
				case 0:
					break;
				case 1:
					bulletTypeData.amplitude = float(behaviourJSONObject[L"amplitude"]->AsNumber());
					bulletTypeData.frequency = float(behaviourJSONObject[L"frequency"]->AsNumber());
					break;
				case 2:
					break;
			}
			bulletTypeData.delayMultiplier = float(behaviourJSONObject[L"delayMultiplier"]->AsNumber());

			//Light
			JSONObject lightJSONObject = jsonObject[L"light"]->AsObject();
			bulletTypeData.lightProperties.size = lightJSONObject[L"size"]->AsNumber();
			JSONObject lightColourJSONObject = lightJSONObject[L"colour"]->AsObject();
			bulletTypeData.lightProperties.colour.r = unsigned int(lightColourJSONObject[L"red"]->AsNumber());
			bulletTypeData.lightProperties.colour.g = unsigned int(lightColourJSONObject[L"green"]->AsNumber());
			bulletTypeData.lightProperties.colour.b = unsigned int(lightColourJSONObject[L"blue"]->AsNumber());
			bulletTypeData.lightProperties.colour.a = unsigned int(lightColourJSONObject[L"alpha"]->AsNumber());
			JSONObject lightOffsetJSONObject = lightJSONObject[L"offset"]->AsObject();
			bulletTypeData.lightProperties.offset.x = float(lightOffsetJSONObject[L"x"]->AsNumber());
			bulletTypeData.lightProperties.offset.y = float(lightOffsetJSONObject[L"y"]->AsNumber());

			//Animations
			JSONArray texturesJSONArray = jsonObject[L"textureURLs"]->AsArray();
			unsigned int texturesJSONArrayLength = texturesJSONArray.size();
			for(unsigned int texturesJSONArrayIndex = 0; texturesJSONArrayIndex < texturesJSONArrayLength; ++texturesJSONArrayIndex)
			{
				bulletTypeData.textureURLs.push_back(StringHelper::wideStringToString(texturesJSONArray[texturesJSONArrayIndex]->AsString()));
			}

			bulletTypeData.animationSpeed = float(jsonObject[L"animationSpeed"]->AsNumber());
			JSONObject spriteDimensionsJSONObject = jsonObject[L"spriteDimensions"]->AsObject();
			bulletTypeData.spriteDimensions.x = float(spriteDimensionsJSONObject[L"width"]->AsNumber());
			bulletTypeData.spriteDimensions.y = float(spriteDimensionsJSONObject[L"height"]->AsNumber());
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

				bulletTypeData.animations[animationID] = frames;
			}

			//return the bullet data
			return bulletTypeData;
		}
		virtual ~BulletTypeData()
		{
		}

		unsigned int typeID;
		bool playerBullet;
		float power;
		float speed;
		float lifetime;
		bool bounceOffWalls;
		float collisionSize;
		bool doRayCastCheckOnBulletTravelPath;
		unsigned int minPerShot;
		unsigned int maxPerShot;
		unsigned int minBulletSpread;
		unsigned int maxBulletSpread;
		unsigned int minBulletAccuracyOffset;
		unsigned int maxBulletAccuracyOffset;
		BULLET_BEHAVIOUR_TYPE behaviourTypeID;
		float delayMultiplier;
		float amplitude;
		float frequency;
		LightProperties lightProperties;
		std::vector<std::string> textureURLs;
		float animationSpeed;
		Vector2<float> spriteDimensions;
		std::map<std::string, std::vector<unsigned int>> animations;
		std::string shootSoundURL;
		std::string destroySoundURL;

	private:
		BulletTypeData()
		{
		}
};

class BulletTypeDataManager
{
	public:
		BulletTypeDataManager();
		virtual ~BulletTypeDataManager();
		static BulletTypeDataManager *Get();
		void init(std::vector<std::string> &resourceURLs);
		BaseBullet *createBullet(unsigned int typeID, GameScene &gameScene, Vector2<float> bulletPosition, Vector2<float> shootDirection, COLLISION_LAYERS collisionLayer, COLLISION_LAYERS collisionCheckingLayer);
		const BulletTypeData &getBulletTypeData(unsigned int typeID);
		unsigned int getRandomBulletTypeID(bool playerBullet);
	private:
		static BulletTypeDataManager *_instance;
		std::vector<BulletTypeData> _bulletTypeDatas;
};

#endif