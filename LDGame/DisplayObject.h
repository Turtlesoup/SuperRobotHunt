#ifndef DISPLAY_OBJECT_H
#define DISPLAY_OBJECT_H

#include "TransformableObject.h"
#include "Vector2.h"

class SpriteBatch;

class DisplayObject : public TransformableObject
{
	public:
		DisplayObject(Vector2<float> position);
		virtual ~DisplayObject();
		bool getVisible();
		void setVisible(bool value);
		void render(SpriteBatch &spriteBatch, sf::Transform &transform);
	protected:
		bool _visible;
	private:
		float *tempTransform;
};

#endif