#ifndef CHASE_EXPLODE_AI_H
#define CHASE_EXPLODE_AI_H

#include "ChaseAI.h"

struct ChaseExplodeAIData : public ChaseAIData
{
	public:
		ChaseExplodeAIData(unsigned int aiType,
						   float movementDurationBeforeCheckDelay,
						   float checkLocationDelayTime,
						   bool onlyFollowWhenDetected,
						   float movePathDirectionX,
						   float movePathDirectionY,
						   float explodeDelayTime,
						   float explodeHitRadius,
						   float explodeHitForce) : ChaseAIData(aiType,
																movementDurationBeforeCheckDelay,
																checkLocationDelayTime,
																onlyFollowWhenDetected,
																movePathDirectionX,
																movePathDirectionY),
													explodeDelayTime(explodeDelayTime),
													explodeHitRadius(explodeHitRadius),
													explodeHitForce(explodeHitForce)
		{
		}
		virtual ~ChaseExplodeAIData(){}
		float explodeDelayTime;
		float explodeHitRadius;
		float explodeHitForce;
};

class ChaseExplodeAI : public ChaseAI
{
	public:
		ChaseExplodeAI(Enemy *parent,
					   float movementDurationBeforeCheckDelay,
					   float checkLocationDelayTime,
					   bool onlyFollowWhenDetected,
					   float movePathDirectionX,
					   float movePathDirectionY,
					   float explodeDelayTime,
					   float explodeHitRadius,
					   float explodeHitForce);
		virtual ~ChaseExplodeAI();
		virtual void update(float deltaTime);
		virtual void onDetected();
		virtual void onUndetected();
	private:
		float _currentExplodeDelayTime;
		const float EXPLODE_DELAY_TIME;
		const float EXPLODE_HIT_RADIUS;
		const float EXPLODE_HIT_FORCE;
};

#endif