#ifndef EMITTING_OBJECT_H
#define EMITTING_OBJECT_H

#include <SFML\Graphics.hpp>
#include "SceneLayer.h"
#include "AnimatedDisplayObject.h"

class FlickeringLight;
class SceneLayer;

class EmittingObject : public AnimatedDisplayObject
{
	public:
		EmittingObject(const std::string& fileName,
				       const std::string& textureName,
					   Vector2<float> position,
					   float animationSpeed,
					   Vector2<float> spriteDimensions,
					   const sf::Color& lightColour,
					   float lightSize,
					   SceneLayer* lightSceneLayer,
					   const Vector2<float>& lightOffset);
		virtual ~EmittingObject();
		virtual void setX(const float value);
		virtual void setY(const float value);
		virtual void setVisible(bool value);
		virtual void onAdded(SceneLayer *sceneLayer, GameObject *parent);
		virtual void onRemoved(bool deletingObject);
	protected:
		FlickeringLight* _light;
		SceneLayer* _lightSceneLayer;
		Vector2<float> _lightOffset;
};

#endif