#ifndef TRANSFORMABLE_OBJECT_H
#define TRANSFORMABLE_OBJECT_H

#include "Vector2.h"
#include "GameObject.h"

class TransformableObject : public virtual GameObject
{
	public:
		TransformableObject(Vector2<float> position);
		virtual ~TransformableObject();
		virtual void setX(float value);
		virtual float getX();
		virtual void setY(float value);
		virtual float getY();
		virtual void setXOffset(float value);
		virtual float getXOffset();
		virtual void setYOffset(float value);
		virtual float getYOffset();
		virtual void setScale(float scaleX, float scaleY);
		virtual void setScale(Vector2<float> scale);
		virtual Vector2<float> &getScale();
		virtual void setRotation(float angle);
		virtual float getRotation();
		virtual void setOrigin(Vector2<float> origin);
		virtual Vector2<float> &getOrigin();
	protected:
		Vector2<float> _position;
		Vector2<float> _offset;
		Vector2<float> _scale;
		float _angle;
		Vector2<float> _origin;
};

#endif