#ifndef CHASE_AI_H
#define CHASE_AI_H

#include "BaseAI.h"
#include "Vector2.h"

struct ChaseAIData : public BaseAIData
{
	public:
		ChaseAIData(unsigned int aiType,
					float movementDurationBeforeCheckDelay,
					float checkLocationDelayTime,
					bool onlyFollowWhenDetected,
					float movePathDirectionX,
					float movePathDirectionY) : BaseAIData(aiType),
												movementDurationBeforeCheckDelay(movementDurationBeforeCheckDelay),
												checkLocationDelayTime(checkLocationDelayTime),
												onlyFollowWhenDetected(onlyFollowWhenDetected),
												movePathDirectionX(movePathDirectionX),
												movePathDirectionY(movePathDirectionY)
												{}
		virtual ~ChaseAIData(){}
		float movementDurationBeforeCheckDelay;
		float checkLocationDelayTime;
		bool onlyFollowWhenDetected;
		float movePathDirectionX;
		float movePathDirectionY;
};

class ChaseAI : public BaseAI
{
	public:
		ChaseAI(Enemy *parent,
			    float movementDurationBeforeCheckDelay,
				float checkLocationDelayTime,
				bool onlyFollowWhenDetected,
				float movePathDirectionX,
				float movePathDirectionY);
		virtual ~ChaseAI();
		virtual void update(float deltaTime);
		virtual void onDetected();
		virtual void onUndetected();
		virtual bool isChasing();
		virtual void onHitBoundsLeft();
		virtual void onHitBoundsRight();
		virtual void onHitBoundsTop();
		virtual void onHitBoundsBottom();
	protected:
		bool _isChasing;
		float _currentMovementDurationBeforeCheckDelay;
		float _checkLocationDelayTime;
		Vector2<float> _targetDirection;
		const float MOVEMENT_DURATION_BEFORE_CHECK_DELAY;
		const float CHECK_LOCATION_DELAY_TIME;
		const bool ONLY_FOLLOW_WHEN_DETECTED;
		float _movePathDirectionX;
		float _movePathDirectionY;
};

#endif