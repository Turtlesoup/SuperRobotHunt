#include "TransformableObject.h"
#include "Application.h"
#include "MathHelper.h"

TransformableObject::TransformableObject(Vector2<float> position) : GameObject(),
																	_position(position),
																	_scale(Vector2<float>(1,1)),
																	_angle(0)
{
}

TransformableObject::~TransformableObject()
{
}

void TransformableObject::setX(float value)
{
	if(MathHelper::isNaN<float>(value))
	{
		throw std::exception("Value is NAN");
	}
	_position.x = value;
}

float TransformableObject::getX()
{
	return _position.x;
}

void TransformableObject::setY(float value)
{
	if(MathHelper::isNaN<float>(value))
	{
		throw std::exception("Value is NAN");
	}
	_position.y = value;
}

float TransformableObject::getY()
{
	return _position.y;
}

void TransformableObject::setXOffset(float value)
{
	if(MathHelper::isNaN<float>(value))
	{
		throw std::exception("Value is NAN");
	}
	_offset.x = value;
}

float TransformableObject::getXOffset()
{
	return _offset.x;
}

void TransformableObject::setYOffset(float value)
{
	if(MathHelper::isNaN<float>(value))
	{
		throw std::exception("Value is NAN");
	}
	_offset.y = value;
}

float TransformableObject::getYOffset()
{
	return _offset.y;
}

void TransformableObject::setScale(float scaleX, float scaleY)
{
	_scale.x = scaleX;
	_scale.y = scaleY;
}

void TransformableObject::setScale(Vector2<float> scale)
{
	_scale = scale;
}

Vector2<float> &TransformableObject::getScale()
{
	return _scale;
}

void TransformableObject::setRotation(float angle)
{
	_angle = angle;
}

float TransformableObject::getRotation()
{
	return _angle;
}

void TransformableObject::setOrigin(Vector2<float> origin)
{
	_origin = origin;
}

Vector2<float> &TransformableObject::getOrigin()
{
	return _origin;
}