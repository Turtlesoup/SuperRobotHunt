#include "Application.h"
#include "SpriteBatch.h"
#include "DisplayObject.h"
#include "TextureManager.h"

DisplayObject::DisplayObject(Vector2<float> position) : TransformableObject(position),
														_visible(true)
{
	tempTransform = new float[16];
}

DisplayObject::~DisplayObject()
{
	delete[] tempTransform;
}

bool DisplayObject::getVisible()
{
	return _visible;
}

void DisplayObject::setVisible(bool value)
{
	_visible = value;
}

void DisplayObject::render(SpriteBatch &spriteBatch, sf::Transform &transform)
{
	if(_visible)
	{
		//create a copy of the transform before applying translation, rotation and scale.
		memcpy((void*)tempTransform, transform.getMatrix(), 16*sizeof(float));

		//update the transform
		transform.translate(_position.x - _origin.x + _offset.x, _position.y - _origin.y + _offset.y).rotate(_angle, _origin.x, _origin.y).scale(_scale.x, _scale.y, _origin.x, _origin.y);

		//render the children
		TransformableObject::render(spriteBatch, transform);

		//undo the changes to the tranform
		memcpy((void*)transform.getMatrix(), tempTransform, 16*sizeof(float));
	}
}