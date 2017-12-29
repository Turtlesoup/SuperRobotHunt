#include "MovePathAI.h"
#include "MathHelper.h"
#include "Player.h"
#include "Enemy.h"
#include "AnimConsts.h"

MovePathAI::MovePathAI(Enemy *parent, float movePathDirectionX, float movePathDirectionY) : BaseAI(parent),
																							_movePathDirectionX(movePathDirectionX),
																							_movePathDirectionY(movePathDirectionY)
{
	_aiTypeID = AI_TYPE_CHASE;

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

MovePathAI::~MovePathAI()
{
}

void MovePathAI::update(float deltaTime)
{
	BaseAI::update(deltaTime);

	float speed = _parent->NORMAL_MOVEMENT_SPEED * deltaTime;
	float xSpeed = _movePathDirectionX * speed;
	float ySpeed = _movePathDirectionY * speed;
	float angle = 0;

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

	std::string animationName;

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

	if(_parent->currenAnimationName() != animationName)
	{
		_parent->currenAnimationName() = animationName;
		_parent->play(_parent->currenAnimationName());
	}

	//move the enemy towards the player
	_parent->setX(_parent->getX() + xSpeed);
	_parent->setY(_parent->getY() + ySpeed);
}

void MovePathAI::onDetected()
{
	BaseAI::onDetected();
}

void MovePathAI::onUndetected()
{
	BaseAI::onUndetected();
}

void MovePathAI::onHitBoundsLeft()
{
	_movePathDirectionX = -_movePathDirectionX;
}

void MovePathAI::onHitBoundsRight()
{
	_movePathDirectionX = -_movePathDirectionX;
}

void MovePathAI::onHitBoundsTop()
{
	_movePathDirectionY = -_movePathDirectionY;
}

void MovePathAI::onHitBoundsBottom()
{
	_movePathDirectionY = -_movePathDirectionY;
}