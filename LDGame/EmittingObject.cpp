#include "EmittingObject.h"
#include "FlickeringLight.h"

EmittingObject::EmittingObject(const std::string& fileName,
							   const std::string& textureName,
							   Vector2<float> position,
							   float animationSpeed,
							   Vector2<float> spriteDimensions,
							   const sf::Color& lightColour,
							   float lightSize,
							   SceneLayer* lightSceneLayer,
							   const Vector2<float>& lightOffset)
							   : AnimatedDisplayObject(fileName, textureName, position, animationSpeed, spriteDimensions),
																																																																				 _lightSceneLayer(lightSceneLayer),
																																																																				 _lightOffset(lightOffset)
{
	_light = new FlickeringLight(Vector2<float>(position.x + _lightOffset.x, position.y + _lightOffset.y), lightColour, lightSize, 100);
}

EmittingObject::~EmittingObject()
{
}

void EmittingObject::setX(float value)
{
	AnimatedDisplayObject::setX(value);
	_light->setX(getX() + _lightOffset.x);
}

void EmittingObject::setY(float value)
{
	AnimatedDisplayObject::setY(value);
	_light->setY(getY() + _lightOffset.y);
}

void EmittingObject::setVisible(bool value)
{
	AnimatedDisplayObject::setVisible(value);
	_light->setVisible(value);
}

void EmittingObject::onAdded(SceneLayer *sceneLayer, GameObject *parent)
{
	AnimatedDisplayObject::onAdded(sceneLayer, parent);
	_lightSceneLayer->addChild(_light);
}

void EmittingObject::onRemoved(bool deletingObject)
{
	AnimatedDisplayObject::onRemoved(deletingObject);
	_lightSceneLayer->removeChild(_light, deletingObject);
}