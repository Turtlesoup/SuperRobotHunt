#include "BaseAI.h"
#include "Enemy.h"

BaseAI::BaseAI(Enemy *parent) : _parent(parent),
								_aiTypeID(AI_TYPE_NONE),
								_hasDetectedPlayer(false)
{
}

BaseAI::~BaseAI()
{
}

unsigned int BaseAI::aiTypeID()
{
	return _aiTypeID;
}

void BaseAI::update(float deltaTime)
{
}

void BaseAI::onDetected()
{
	_hasDetectedPlayer = true;
}

void BaseAI::onUndetected()
{
	_hasDetectedPlayer = false;
}

bool BaseAI::hasDetectedPlayer()
{
	return _hasDetectedPlayer;
}

void BaseAI::onHitBoundsLeft()
{
}

void BaseAI::onHitBoundsRight()
{
}

void BaseAI::onHitBoundsTop()
{
}

void BaseAI::onHitBoundsBottom()
{
}