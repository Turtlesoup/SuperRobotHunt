#include "OneShotEffect.h"
#include "GameObject.h"
#include "SceneLayer.h"
#include "MathHelper.h"

OneShotEffect::OneShotEffect(const std::string& fileName,
							 const std::string& textureName,
							 Vector2<float> position,
							 float animationSpeed,
							 Vector2<float> spriteDimensions,
							 const sf::Color& lightColour,
							 float lightSize,
							 SceneLayer* lightSceneLayer,
							 const Vector2<float>& lightOffset,
							 GameScene& gameScene) :
							 EmittingObject(fileName,
											textureName,
											position,
											animationSpeed,
											spriteDimensions,
											lightColour,
											lightSize,
											lightSceneLayer,
											lightOffset),
							 _gameScene(gameScene)
{
}

OneShotEffect::~OneShotEffect()
{
}

void OneShotEffect::setAnimationFrames(const std::vector<unsigned int> animationframes)
{
	addAnimation("idle", animationframes);
	addOnAnimationCompleteCallback(std::bind<void>(&OneShotEffect::onAnimationComplete, this));
}

void OneShotEffect::onAdded(SceneLayer *sceneLayer, GameObject *parent)
{
	EmittingObject::onAdded(sceneLayer, parent);

	play("idle");
}

void OneShotEffect::onRemoved(bool deletingObject)
{
	//stop the animation playing
	stop();

	//remove callback
	removeOnAnimationCompleteCallback();

	//remove the object
	EmittingObject::onRemoved(deletingObject);
}

void OneShotEffect::onAnimationComplete()
{
	//remove and delete the object
	_gameScene.overObjectsLayer()->removeChild(this, true);
}
