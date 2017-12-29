#include "Enemy.h"
#include "TransformableObject.h"
#include "Player.h"
#include "Gun.h"
#include "Explosion.h"
#include "MathHelper.h"
#include "AudioManager.h"
#include "ChaseAI.h"
#include "ChaseExplodeAI.h"
#include "MovePathAI.h"
#include "AnimConsts.h"
#include <map>
#include <vector>
#include <string>

Enemy::Enemy(const Vector2<float> &position,
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
			 const std::string &destroySoundURL)
			 : EmittingObject(fileName, textureName, position, 75, spriteDimensions, lightProperties.colour, lightProperties.size, lightSceneLayer, lightProperties.offset),
			   CollidableObject(COLLISION_LAYERS::LAYER_2),
			   _lootTypes(lootTypes),
			   _gameScene(gameScene),
			   _aimGunsAtPlayer(aimGunsAtPlayer),
			   _guns(guns),
			   _currentDirection(DIRECTION::UP),
			   _hitDirection(DIRECTION::UP),
			   NORMAL_MOVEMENT_SPEED(normalMovementSpeed),
			   CHASE_MOVEMENT_SPEED(chaseMovementSpeed),
			   DETECTION_DISTANCE_THRESHOLD(detectionDistanceThreshold),
			   MAX_HEALTH(maxHealth),
			   DESTROY_SCORE(destroyScore),
			   _health(maxHealth),
			   _dead(false),
			   _currentHitDelay(0),
			   HIT_DELAY(hitDelay),
			   HIT_FORCE(hitForce),
			   CRITICAL_HIT_MULTIPLIER(criticalHitMultiplier),
		       CRITICAL_HIT_PERCENTAGE(criticalHitPercentage),
			   SPAWN_SOUND_URL(spawnSoundURL),
			   DESTROY_SOUND_URL(destroySoundURL),
			   SPAWN_DURATION(200.0f),
			   SPAWN_HEIGHT_OFFSET(100.0f),
			   _currentSpawnDuration(SPAWN_DURATION),
			   _originalWidth(0.0f),
			   _originalY(0.0f)
{
	//create the ai instance
	switch(aiData->AI_TYPE)
	{
		case AI_TYPE_NONE:
			_ai = new BaseAI(this);
			break;
		case AI_TYPE_CHASE:
			{
				ChaseAIData *chaseAIData = dynamic_cast<ChaseAIData*>(aiData);
				_ai = new ChaseAI(this, chaseAIData->movementDurationBeforeCheckDelay, chaseAIData->checkLocationDelayTime, chaseAIData->onlyFollowWhenDetected, chaseAIData->movePathDirectionX, chaseAIData->movePathDirectionY);
			}
			break;
		case AI_TYPE_CHASE_EXPLODE:
			{
				ChaseExplodeAIData *chaseExplodeAIData = dynamic_cast<ChaseExplodeAIData*>(aiData);
				_ai = new ChaseExplodeAI(this, chaseExplodeAIData->movementDurationBeforeCheckDelay, chaseExplodeAIData->checkLocationDelayTime, chaseExplodeAIData->onlyFollowWhenDetected, chaseExplodeAIData->movePathDirectionX, chaseExplodeAIData->movePathDirectionY, chaseExplodeAIData->explodeDelayTime, chaseExplodeAIData->explodeHitRadius, chaseExplodeAIData->explodeHitForce);
			}
			break;
		case AI_TYPE_MOVE_PATH:
			{
				MovePathAIData *movePathAI = dynamic_cast<MovePathAIData*>(aiData);
				_ai = new MovePathAI(this, movePathAI->movePathDirectionX, movePathAI->movePathDirectionY);
			}
			break;
	}

	//add the animations
	std::map<std::string, std::vector<unsigned int>>::const_iterator animationsIterator, animationsEnd;
	animationsEnd = animations.end();
	for(animationsIterator = animations.begin(); animationsIterator != animationsEnd; ++animationsIterator)
	{
		addAnimation((*animationsIterator).first, (*animationsIterator).second);
	}

	//initialise with the first animation
	_currenAnimationName = (*animations.begin()).first;
	play(_currenAnimationName);

	//set the collision bounds
	setCollisionBounds(Rect<int>(_position.x - (_width*0.5), _position.y - (_height*0.5), _width, _height));
	setCollidable(true);
}

Enemy::~Enemy()
{
}

void Enemy::setTarget(Player* target)
{
	_target = target;
}

Player *Enemy::getTarget()
{
	return _target;
}

void Enemy::hit(float xDirection, float yDirection, float power)
{
	if(_currentHitDelay <= 0)
	{
		bool critical = (rand()%100 < CRITICAL_HIT_PERCENTAGE);
		if(critical)
		{
			power *= CRITICAL_HIT_MULTIPLIER;
		}

		_health -= power;
		if(_health <= 0 && !_dead)
		{
			_dead = true;
			destroy();
		}
		else
		{
			_currentHitDelay = HIT_DELAY;
			_hitDirection = Directions::valuesToDirection(xDirection, yDirection);

			setCollisionBoundsLeft(_position.x - (_width*0.5));
			setCollisionBoundsTop(_position.y - (_height*0.5));

			//play hit animaion
			std::string animationName;

			switch(_currentDirection)
			{
				case DIRECTION::UP:
					animationName = FLICKER_UP;
					break;
				case DIRECTION::LEFT:
					animationName = FLICKER_LEFT;
					break;
				case DIRECTION::DOWN:
					animationName = FLICKER_DOWN;
					break;
				case DIRECTION::RIGHT:
					animationName = FLICKER_RIGHT;
					break;
			}

			if(_currenAnimationName != animationName)
			{
				_currenAnimationName = animationName;
				play(_currenAnimationName);
			}

			//display the hit value and shake the screen
			_gameScene.onEnemyHit(power, _position, critical);
		}
	}
}

void Enemy::update(float deltaTime)
{
	EmittingObject::update(deltaTime);

	if(_currentSpawnDuration > 0)
	{
		//countdown spawn time and update the width of the enemy accordingly,
		//this creates the spawn effect for new enemies on the board.
		_currentSpawnDuration -= deltaTime;
		float spawnDurationPercentage = (SPAWN_DURATION-_currentSpawnDuration)/SPAWN_DURATION;
		sf::Color &tint = getTint();

		if(_currentSpawnDuration <= 0)
		{
			setCollidable(true);
			setWidth(_originalWidth);
			tint.r = 255;
			tint.g = 255;
			tint.b = 255;
			_position.y = _originalY;
		}
		else
		{
			if(spawnDurationPercentage > 0.5)
			{
				setWidth(_originalWidth*((spawnDurationPercentage-0.5)*2));
			}
			else
			{
				setWidth(1.0f);
			}
			tint.r = 255*spawnDurationPercentage;
			tint.g = 255*spawnDurationPercentage;
			tint.b = 255*spawnDurationPercentage;
			if(spawnDurationPercentage <= 0.5)
			{
				_position.y = _originalY - ((1-(spawnDurationPercentage*2)) * SPAWN_HEIGHT_OFFSET);
			}
		}
	}
	else
	{
		//hit motion
		if(_currentHitDelay > 0)
		{
			_currentHitDelay -= deltaTime;

			float hitForce = HIT_FORCE * (_currentHitDelay/HIT_DELAY) * deltaTime;

			switch(_hitDirection)
			{
				case DIRECTION::UP:
					setY(_position.y - hitForce);
					break;
				case DIRECTION::DOWN:
					setY(_position.y + hitForce);
					break;
				case DIRECTION::LEFT:
					setX(_position.x - hitForce);
					break;
				case DIRECTION::RIGHT:
					setX(_position.x + hitForce);
					break;
			}

			if(_position.x > _gameScene.getScreenBoundsMaxX())
			{
				_position.x = _gameScene.getScreenBoundsMaxX();
				_ai->onHitBoundsRight();
			}
			else if(_position.x < _gameScene.getScreenBoundsMinX())
			{
				_position.x = _gameScene.getScreenBoundsMinX();
				_ai->onHitBoundsLeft();
			}
			if(_position.y > _gameScene.getScreenBoundsMaxY())
			{
				_position.y = _gameScene.getScreenBoundsMaxY();
				_ai->onHitBoundsBottom();
			}
			else if(_position.y < _gameScene.getScreenBoundsMinY())
			{
				_position.y = _gameScene.getScreenBoundsMinY();
				_ai->onHitBoundsTop();
			}
		}
		else
		{
			//if the enemy has an active target
			if(!_target->isDead())
			{
				//update the target direction
				_targetDirection.x = _target->getX() - _position.x;
				_targetDirection.y = _target->getY() - _position.y;
				MathHelper::normaliseVector2f(_targetDirection);

				//check if the enemy is within its detection distance of the player and update the ai accordingly
				float distance = MathHelper::distance(_position, Vector2<float>(_target->getX(), _target->getY()));
				if(!_ai->hasDetectedPlayer() && distance <= DETECTION_DISTANCE_THRESHOLD)
				{
					_ai->onDetected();
				}
				else if(_ai->hasDetectedPlayer() && distance > DETECTION_DISTANCE_THRESHOLD)
				{
					_ai->onUndetected();
				}

				//bounds check
				if(_position.x > _gameScene.getScreenBoundsMaxX())
				{
					_position.x = _gameScene.getScreenBoundsMaxX();
					_ai->onHitBoundsRight();
				}
				else if(_position.x < _gameScene.getScreenBoundsMinX())
				{
					_position.x = _gameScene.getScreenBoundsMinX();
					_ai->onHitBoundsLeft();
				}
				if(_position.y > _gameScene.getScreenBoundsMaxY())
				{
					_position.y = _gameScene.getScreenBoundsMaxY();
					_ai->onHitBoundsBottom();
				}
				else if(_position.y < _gameScene.getScreenBoundsMinY())
				{
					_position.y = _gameScene.getScreenBoundsMinY();
					_ai->onHitBoundsTop();
				}

				//update the ai module
				_ai->update(deltaTime);

				//update collision bound position
				setCollisionBoundsLeft(_position.x - (_width*0.5));
				setCollisionBoundsTop(_position.y - (_height*0.5));

				if(_aimGunsAtPlayer && _ai->hasDetectedPlayer())
				{
					//compute the shoot angle
					float angle = MathHelper::getDegreesFromVector(_targetDirection);

					//shoot each gun towards the target
					unsigned int gunLength = _guns.size();
					for(unsigned int gunIndex = 0; gunIndex < gunLength; ++gunIndex)
					{
						_guns[gunIndex]->shoot(_position, angle);
					}
				}
				else if(!_aimGunsAtPlayer)
				{
					//compute the shoot angle
					float angle = 0.0f;
					switch(_currentDirection)
					{
						case DIRECTION::UP:
							angle = 180.0f;
							break;
						case DIRECTION::DOWN:
							angle = 0.0f;
							break;
						case DIRECTION::LEFT:
							angle = 90.0f;
							break;
						case DIRECTION::RIGHT:
							angle = 270.0f;
							break;
					}

					//shoot each gun towards the target
					unsigned int gunLength = _guns.size();
					for(unsigned int gunIndex = 0; gunIndex < gunLength; ++gunIndex)
					{
						_guns[gunIndex]->shoot(_position, angle);
					}
				}
			}
		}
	}
}

void Enemy::spawn()
{
	//play the spawn sfx
	AudioManager::Get()->playSound(SPAWN_SOUND_URL);

	//setup the spawn animation
	_currentSpawnDuration = SPAWN_DURATION;
	_originalWidth = getWidth();
	_originalY = _position.y;
	setCollidable(false);
	setWidth(1.0f);
	setTint(sf::Color(0,0,0));
}

void Enemy::destroy()
{
	//create the explosion object
	_gameScene.overObjectsLayer()->addChild(new Explosion(_position, _gameScene));

	//remove and destroy the enemy
	_gameScene.gameLayer()->removeChild(this, true);

	//spawn the loot
	_gameScene.spawnLoot(_lootTypes, _position);

	//award the score and spawn the points indicator
	_gameScene.onEnemyDestroyed(DESTROY_SCORE, _position);

	//shake the screen to signify a hit
	_gameScene.setShakingTime(100);

	//play the destroy sfx
	AudioManager::Get()->playSound(DESTROY_SOUND_URL);
}

void Enemy::onCollision(CollidableObject* collidingObject)
{
	if(collidingObject == _target)
	{
		//collided with the target
		_target->hit(_target->getX() - _position.x, _target->getY() - _position.y, 1);
	}
}

void Enemy::onRayCollision(CollidableObject* collidingObject, Ray *ray, float rayIntersectionDistance)
{
	if(collidingObject == _target)
	{
		//collided with the target
	}
}

void Enemy::onAdded(SceneLayer *sceneLayer, GameObject *parent)
{
	EmittingObject::onAdded(sceneLayer, parent);
	unsigned int gunLength = _guns.size();
	for(unsigned int gunIndex = 0; gunIndex < gunLength; ++gunIndex)
	{
		_gameScene.overObjectsLayer()->addChild(_guns[gunIndex]);
	}
}

void Enemy::onRemoved(bool deletingObject)
{
	EmittingObject::onRemoved(deletingObject);
	unsigned int gunLength = _guns.size();
	for(unsigned int gunIndex = 0; gunIndex < gunLength; ++gunIndex)
	{
		_gameScene.overObjectsLayer()->removeChild(_guns[gunIndex], deletingObject);
	}
}

Vector2<float> &Enemy::targetDirection()
{
	return _targetDirection;
}

DIRECTION &Enemy::currentDirection()
{
	return _currentDirection;
}

std::string &Enemy::currenAnimationName()
{
	return _currenAnimationName;
}