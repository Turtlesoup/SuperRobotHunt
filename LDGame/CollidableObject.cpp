#include "CollidableObject.h"
#include "Ray.h"

CollidableObject::CollidableObject(COLLISION_LAYERS collisionLayer, COLLISION_LAYERS collisionCheckingLayer) : GameObject(),
																											   _collidable(false),
																											   _collisionChecking(false),
																											   _collisionLayer(collisionLayer),
																											   _collisionCheckingLayer(collisionCheckingLayer)
{
}

CollidableObject::~CollidableObject()
{
}

Rect<int> &CollidableObject::getCollisionBounds()
{
	return _collisionBounds;
}

void CollidableObject::setCollisionBounds(const Rect<int> &collisionBounds)
{
	_collisionBounds = collisionBounds;
}

bool CollidableObject::getCollidable()
{
	return _collidable;
}

bool CollidableObject::getCollisionChecking()
{
	return _collisionChecking;
}

void CollidableObject::setCollisionChecking(bool collisionChecking)
{
	_collisionChecking = collisionChecking;
}

void CollidableObject::setCollidable(bool collidable)
{
	_collidable = collidable;
}

int CollidableObject::getCollisionBoundsLeft()
{
	return _collisionBounds.left;
}

int CollidableObject::getCollisionBoundsTop()
{
	return _collisionBounds.top;
}

int CollidableObject::getCollisionBoundsWidth()
{
	return _collisionBounds.width;
}

int CollidableObject::getCollisionBoundsHeight()
{
	return _collisionBounds.height;
}

void CollidableObject::setCollisionBoundsLeft(int value)
{
	_collisionBounds.left = value;
}

void CollidableObject::setCollisionBoundsTop(int value)
{
	_collisionBounds.top = value;
}

void CollidableObject::setCollisionBoundsWidth(int value)
{
	_collisionBounds.width = value;
}

void CollidableObject::setCollisionBoundsHeight(int value)
{
	_collisionBounds.height = value;
}

COLLISION_LAYERS CollidableObject::getCollisionLayer()
{
	return _collisionLayer;
}

void CollidableObject::setCollisionLayer(COLLISION_LAYERS collisionLayer)
{
	_collisionLayer = collisionLayer;
}

COLLISION_LAYERS CollidableObject::getCollisionCheckingLayer()
{
	return _collisionCheckingLayer;
}

void CollidableObject::setCollisionCheckingLayer(COLLISION_LAYERS collisionCheckingLayer)
{
	_collisionCheckingLayer = collisionCheckingLayer;
}