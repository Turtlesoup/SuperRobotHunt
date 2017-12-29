#ifndef ENEMY_H
#define ENEMY_H

#include "EmittingObject.h"
#include "CollidableObject.h"
#include "GameScene.h"
#include "Directions.h"
#include "LootTypes.h"
#include "Light.h"
#include "Directions.h"
#include "EnemyTypeDataManager.h"
#include <vector>

class Player;
class Gun;
class BaseAI;

class Enemy : public EmittingObject, public CollidableObject
{
	public:
		Enemy(const Vector2<float> &position,
			  const std::vector<LOOT_TYPES> &lootTypes,
			  GameScene &gameScene,
			  bool aimGunsAtPlayer,
			  const std::vector<Gun*> &guns,
			  BaseAIData *aiData,
			  float normalMovementSpeed,
			  float chaseMovementSpeed,
			  float detectionDistanceThreshold,
			  float maxHealth,
			  unsigned int destroyScore,
			  float hitDelay,
			  float hitForce,
			  float criticalHitMultiplier,
			  float criticalHitPercentage,
			  const std::string &fileName,
			  const std::string &textureName,
			  const Vector2<float> &spriteDimensions,
			  const std::map<std::string, std::vector<unsigned int>> animations,
			  const LightProperties &lightProperties,
			  SceneLayer *lightSceneLayer,
			  const std::string &spawnSoundURL,
			  const std::string &destroySoundURL);
		virtual ~Enemy();
		void setTarget(Player* target);
		Player *getTarget();
		virtual void hit(float xDirection, float yDirection, float power);
		virtual void update(float deltaTime);
		virtual void spawn();
		virtual void destroy();
		virtual void onCollision(CollidableObject* collidingObject);
		virtual void onRayCollision(CollidableObject* collidingObject, Ray *ray, float rayIntersectionDistance);
		void onAdded(SceneLayer *sceneLayer, GameObject *parent);
		void onRemoved(bool deletingObject);
		Vector2<float> &targetDirection();
		DIRECTION &currentDirection();
		std::string &currenAnimationName();
		const float NORMAL_MOVEMENT_SPEED;
		const float CHASE_MOVEMENT_SPEED;
	protected:
		const std::vector<LOOT_TYPES> _lootTypes;
		GameScene& _gameScene;
		bool _aimGunsAtPlayer;
		const std::vector<Gun*> _guns;
		BaseAI *_ai;
		float DETECTION_DISTANCE_THRESHOLD;
		Player* _target;
		DIRECTION _hitDirection;
		const float MAX_HEALTH;
		const unsigned int DESTROY_SCORE;
		float _health;
		bool _dead;
		float _currentHitDelay;
		Vector2<float> _targetDirection;
		DIRECTION _currentDirection;
		std::string _currenAnimationName;
		const float HIT_DELAY;
		const float HIT_FORCE;
		const float CRITICAL_HIT_MULTIPLIER;
		const float CRITICAL_HIT_PERCENTAGE;
		const std::string SPAWN_SOUND_URL;
		const std::string DESTROY_SOUND_URL;
		float _currentSpawnDuration;
		const float SPAWN_DURATION;
		const float SPAWN_HEIGHT_OFFSET;
		float _originalWidth;
		float _originalY;
};

#endif