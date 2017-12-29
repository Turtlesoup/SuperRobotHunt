#ifndef ONE_SHOT_EFFECT_H
#define ONE_SHOT_EFFECT_H

#include <string>
#include "EmittingObject.h"
#include "GameScene.h"
#include "Vector2.h"

class GameObject;
class SceneLayer;

class OneShotEffect : public EmittingObject
{
	public:
		OneShotEffect(const std::string& fileName,
					  const std::string& textureName,
					  Vector2<float> position,
					  float animationSpeed,
					  Vector2<float> spriteDimensions,
					  const sf::Color& lightColour,
					  float lightSize,
					  SceneLayer* lightSceneLayer,
					  const Vector2<float>& lightOffset,
					  GameScene& gameScene);
		virtual ~OneShotEffect();
		void setAnimationFrames(const std::vector<unsigned int> animationframes);
		virtual void onAdded(SceneLayer *sceneLayer, GameObject *parent);
		virtual void onRemoved(bool deletingObject);
	protected:
		GameScene& _gameScene;
		virtual void onAnimationComplete();

};

#endif