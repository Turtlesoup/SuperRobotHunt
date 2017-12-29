#include "ChaseExplodeAI.h"
#include "Enemy.h"
#include "Player.h"
#include "MathHelper.h"
#include "Vector2.h"

ChaseExplodeAI::ChaseExplodeAI(Enemy *parent,
							   float movementDurationBeforeCheckDelay,
							   float checkLocationDelayTime,
							   bool onlyFollowWhenDetected,
							   float movePathDirectionX,
							   float movePathDirectionY,
							   float explodeDelayTime,
							   float explodeHitRadius,
							   float explodeHitForce) : ChaseAI(parent,
																movementDurationBeforeCheckDelay,
																checkLocationDelayTime,
																onlyFollowWhenDetected,
																movePathDirectionX,
																movePathDirectionY),
														EXPLODE_DELAY_TIME(explodeDelayTime),
														EXPLODE_HIT_RADIUS(explodeHitRadius),
														EXPLODE_HIT_FORCE(explodeHitForce),
														_currentExplodeDelayTime(0.0)
{
	_aiTypeID = AI_TYPE_CHASE_EXPLODE;
}

ChaseExplodeAI::~ChaseExplodeAI()
{
}

void ChaseExplodeAI::update(float deltaTime)
{
	ChaseAI::update(deltaTime);

	if(_isChasing)
	{
		_currentExplodeDelayTime += deltaTime;
		if(_currentExplodeDelayTime >= EXPLODE_DELAY_TIME)
		{
			//damage the player if the player is in the vicinity of the explosion
			Player *target = _parent->getTarget();
			float targetX = target->getX();
			float targetY = target->getY();
			float parentX = _parent->getX();
			float parentY = _parent->getY();
			float distance = MathHelper::distance(targetX, targetY, parentX, parentY);
			Vector2<float> targetDirection(targetX - parentX, targetY - parentY);
			if(distance <= EXPLODE_HIT_RADIUS)
			{
				target->hit(targetDirection.x, targetDirection.y, EXPLODE_HIT_FORCE);
			}

			//destroy the enemy
			_parent->destroy();
		}
	}
}

void ChaseExplodeAI::onDetected()
{
	BaseAI::onDetected();
	_isChasing = true;
}

void ChaseExplodeAI::onUndetected()
{
	BaseAI::onUndetected();
}