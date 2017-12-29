#include "ChaseAI.h"
#include "MathHelper.h"
#include "Player.h"
#include "Enemy.h"
#include "AnimConsts.h"

ChaseAI::ChaseAI(Enemy *parent,
				 float movementDurationBeforeCheckDelay,
				 float checkLocationDelayTime,
				 bool onlyFollowWhenDetected,
				 float movePathDirectionX,
				 float movePathDirectionY) : BaseAI(parent),
											 _isChasing(false),
											 MOVEMENT_DURATION_BEFORE_CHECK_DELAY(movementDurationBeforeCheckDelay),
											 CHECK_LOCATION_DELAY_TIME(checkLocationDelayTime),
											 ONLY_FOLLOW_WHEN_DETECTED(onlyFollowWhenDetected),
											 _movePathDirectionX(movePathDirectionX),
											 _movePathDirectionY(movePathDirectionY),
											 _currentMovementDurationBeforeCheckDelay(0.0),
											 _checkLocationDelayTime(CHECK_LOCATION_DELAY_TIME)
{
	_aiTypeID = AI_TYPE_CHASE;
	_currentMovementDurationBeforeCheckDelay = 0.0f;
	_checkLocationDelayTime = CHECK_LOCATION_DELAY_TIME;

	//randomise starting direction
	if(rand() % 2 == 0)
	{
		_movePathDirectionX = -_movePathDirectionX;
	}
	if(rand() % 2 == 0)
	{
		_movePathDirectionY = -_movePathDirectionY;
	}
}

ChaseAI::~ChaseAI()
{
}

void ChaseAI::update(float deltaTime)
{
	BaseAI::update(deltaTime);

	if(_checkLocationDelayTime >= 0.0f)
	{
		_checkLocationDelayTime -= deltaTime;
		if(_checkLocationDelayTime < 0.0f)
		{
			_currentMovementDurationBeforeCheckDelay = MOVEMENT_DURATION_BEFORE_CHECK_DELAY;
			_targetDirection.x = _parent->targetDirection().x;
			_targetDirection.y = _parent->targetDirection().y;
		}
	}

	if(_checkLocationDelayTime <= 0.0f && _currentMovementDurationBeforeCheckDelay >= 0.0f)
	{
		float speed = 0.0f;
		float angle = 0.0f;

		if(_isChasing || !ONLY_FOLLOW_WHEN_DETECTED)
		{
			angle = MathHelper::getDegreesFromVector(_targetDirection) + 90;
		}
		else
		{
			if(abs(_movePathDirectionX) >= abs(_movePathDirectionY))
			{
				if(_movePathDirectionX <= 0)
				{
					angle = 270;
				}
				else
				{
					angle = 90;
				}
			}
			else
			{
				if(_movePathDirectionY < 0)
				{
					angle = 0;
				}
				else
				{
					angle = 180;
				}
			}
		}

		std::string animationName;

		if(_isChasing)
		{
			if(angle >= 45 && angle < 135)
			{
				animationName = CHASE_RIGHT;
				_parent->currentDirection() = DIRECTION::RIGHT;
			}
			else if(angle >= 135 && angle < 225)
			{
				animationName = CHASE_DOWN;
				_parent->currentDirection() = DIRECTION::DOWN;
			}
			else if(angle >= 225 && angle < 315)
			{
				animationName = CHASE_LEFT;
				_parent->currentDirection() = DIRECTION::LEFT;
			}
			else
			{
				animationName = CHASE_UP;
				_parent->currentDirection() = DIRECTION::UP;
			}

			speed = _parent->CHASE_MOVEMENT_SPEED * deltaTime;
		}
		else
		{
			if(angle >= 45 && angle < 135)
			{
				animationName = WALK_RIGHT;
				_parent->currentDirection() = DIRECTION::RIGHT;
			}
			else if(angle >= 135 && angle < 225)
			{
				animationName = WALK_DOWN;
				_parent->currentDirection() = DIRECTION::DOWN;
			}
			else if(angle >= 225 && angle < 315)
			{
				animationName = WALK_LEFT;
				_parent->currentDirection() = DIRECTION::LEFT;
			}
			else
			{
				animationName = WALK_UP;
				_parent->currentDirection() = DIRECTION::UP;
			}

			speed = _parent->NORMAL_MOVEMENT_SPEED * deltaTime;
		}

		if(_parent->currenAnimationName() != animationName)
		{
			_parent->currenAnimationName() = animationName;
			_parent->play(_parent->currenAnimationName());
		}

		//move the enemy towards the player
		if(_isChasing || !ONLY_FOLLOW_WHEN_DETECTED)
		{
			_parent->setX(_parent->getX() + _targetDirection.x*speed);
			_parent->setY(_parent->getY() + _targetDirection.y*speed);
		}
		else
		{
			_parent->setX(_parent->getX() + _movePathDirectionX*speed);
			_parent->setY(_parent->getY() + _movePathDirectionY*speed);
		}
	}

	if(_currentMovementDurationBeforeCheckDelay >= 0.0f)
	{
		_currentMovementDurationBeforeCheckDelay -= deltaTime;
		if(_currentMovementDurationBeforeCheckDelay < 0.0f)
		{
			_checkLocationDelayTime = CHECK_LOCATION_DELAY_TIME;
		}
	}

}

void ChaseAI::onDetected()
{
	BaseAI::onDetected();
	_isChasing = true;
}

void ChaseAI::onUndetected()
{
	BaseAI::onUndetected();
	_isChasing = false;
}

bool ChaseAI::isChasing()
{
	return _isChasing;
}

void ChaseAI::onHitBoundsLeft()
{
	_movePathDirectionX = -_movePathDirectionX;
	_currentMovementDurationBeforeCheckDelay = 0.0f;
	_checkLocationDelayTime = CHECK_LOCATION_DELAY_TIME;
}

void ChaseAI::onHitBoundsRight()
{
	_movePathDirectionX = -_movePathDirectionX;
	_currentMovementDurationBeforeCheckDelay = 0.0f;
	_checkLocationDelayTime = CHECK_LOCATION_DELAY_TIME;
}

void ChaseAI::onHitBoundsTop()
{
	_movePathDirectionY = -_movePathDirectionY;
	_currentMovementDurationBeforeCheckDelay = 0.0f;
	_checkLocationDelayTime = CHECK_LOCATION_DELAY_TIME;
}

void ChaseAI::onHitBoundsBottom()
{
	_movePathDirectionY = -_movePathDirectionY;
	_currentMovementDurationBeforeCheckDelay = 0.0f;
	_checkLocationDelayTime = CHECK_LOCATION_DELAY_TIME;
}