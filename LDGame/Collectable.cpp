#include "Collectable.h"
#include "SceneLayer.h"
#include "Player.h"
#include "GameScene.h"
#include "MathHelper.h"
#include "Resources.h"

Collectable::Collectable(const Vector2<float> &position, GameScene &gameScene, std::string filename, Vector2<float> spriteDimensions, float collectableSize, sf::Color lightColour, float lightSize) : EmittingObject(filename,
																																																					  TEXTURE_ATLAS_SPRITES,
																																																					  position,
																																																					  75,
																																																					  spriteDimensions,
																																																					  lightColour,
																																																					  lightSize,
																																																					  gameScene.underLightLayer(),
																																																					  Vector2<float>(0, 20)),
																																																	   CollidableObject(COLLISION_LAYERS::LAYER_4),
																																																	   _gameScene(gameScene),
																																																	   _collecting(false),
																																																	   COLLECTABLE_SIZE(collectableSize),
																																																	   _bouncing(false),
																																																	   _currentRemovalTime(0.0),
																																																	   _currentFlickerTime(0.0),
																																																	   MIN_BOUNCE_DISTANCE(50),
																																																	   MAX_BOUNCE_DISTANCE(75),
																																																	   BOUNCE_SPEED(0.002),
																																																	   TIME_BEFORE_REMOVAL_FLICKER(10000),
																																																	   TIME_BEFORE_REMOVAL(15000),
																																																	   FLICKER_TIME(100)
{
	setCollisionBounds(Rect<int>(_position.x - (COLLECTABLE_SIZE*0.5), _position.y - (COLLECTABLE_SIZE*0.5), COLLECTABLE_SIZE, COLLECTABLE_SIZE));
	setCollidable(true);
}

Collectable::~Collectable()
{
}

void Collectable::playCollectAnimation()
{
	if(!_collecting)
	{
		setCollidable(false);
		setCollisionChecking(false);
		addOnAnimationCompleteCallback(std::bind<void>(&Collectable::onCollectAnimationComplete, this));
		play("collect");
		_collecting = true;
	}
}

void Collectable::onCollectAnimationComplete()
{
	removeOnAnimationCompleteCallback();

	//remove and delete the collectable game object
	_gameScene.removeChild(this, true);
}

void Collectable::update(float deltaTime)
{
	EmittingObject::update(deltaTime);

	if(_bouncing)
	{
		_currentCurveValue += deltaTime * BOUNCE_SPEED;

		Vector2<float> newPosition = _bounceTweens[_currentBounceTweenIndex].getPoint(_currentCurveValue);

		if(newPosition.x < _gameScene.getScreenBoundsMinX() + (_width*0.5))
		{
			newPosition.x = _gameScene.getScreenBoundsMinX() + (_width*0.5) + (_gameScene.getScreenBoundsMinX() - newPosition.x);
		}
		else if(newPosition.x > _gameScene.getScreenBoundsMaxX() - (_width*0.5))
		{
			newPosition.x = _gameScene.getScreenBoundsMaxX() - (_width*0.5) - (newPosition.x - _gameScene.getScreenBoundsMaxX());
		}

		if(newPosition.y < _gameScene.getScreenBoundsMinY() + (_height*0.5))
		{
			newPosition.y = _gameScene.getScreenBoundsMinY() + (_height*0.5) + (_gameScene.getScreenBoundsMinY() - newPosition.y);
		}
		else if(newPosition.y > _gameScene.getScreenBoundsMaxY() - (_height*0.5))
		{
			newPosition.y = _gameScene.getScreenBoundsMaxY() - (_height*0.5) - (newPosition.y - _gameScene.getScreenBoundsMaxY());
		}

		setX(newPosition.x);
		setY(newPosition.y);

		//update collision bound position
		setCollisionBoundsLeft(_position.x - (_width*0.5));
		setCollisionBoundsTop(_position.y - (_height*0.5));

		if(_currentCurveValue >= 1)
		{
			_currentCurveValue = 0;
			++ _currentBounceTweenIndex;
			if(_currentBounceTweenIndex == _bounceTweens.size())
			{
				//bouncing has completed
				_bouncing = false;
			}
		}
	}

	_currentRemovalTime += deltaTime;
	if(_currentRemovalTime >= TIME_BEFORE_REMOVAL_FLICKER)
	{
		_currentFlickerTime += deltaTime;
		if(_currentFlickerTime >= FLICKER_TIME)
		{
			if(_visible)
			{
				setVisible(false);
			}
			else
			{
				setVisible(true);
			}
			_currentFlickerTime = 0.0;
		}
	}
	if(_currentRemovalTime >= TIME_BEFORE_REMOVAL)
	{
		_gameScene.gameLayer()->removeChild(this, true);
	}
}

void Collectable::onCollected(Player *player)
{
}

void Collectable::onCollision(CollidableObject *collidingObject)
{
	Player *player = dynamic_cast<Player*>(collidingObject);
	if(player)
	{
		//on collected function
		onCollected(player);

		//play the collect animation
		playCollectAnimation();
	}
}

void Collectable::onRayCollision(CollidableObject *collidingObject, Ray *ray, float rayIntersectionDistance)
{
	Player *player = dynamic_cast<Player*>(collidingObject);
	if(player)
	{
		//on collected function
		onCollected(player);

		//play the collect animation
		playCollectAnimation();
	}
}

void Collectable::doBounceAnimation()
{
	_currentBounceTweenIndex = 0;
	_currentCurveValue = 0;

	float bounceDistance = MIN_BOUNCE_DISTANCE + (MathHelper::randomFloat()*(MAX_BOUNCE_DISTANCE - MIN_BOUNCE_DISTANCE));
	float xAdvance = (MathHelper::randomFloat()*2) - 1;
	float yAdvance = (MathHelper::randomFloat()*2) - 1;

	addBounceTween(_position.x, _position.y, xAdvance, yAdvance, bounceDistance);
	addBounceTween(_position.x + (xAdvance * bounceDistance), _position.y + (yAdvance * bounceDistance), xAdvance, yAdvance, bounceDistance * 0.5);
	addBounceTween(_position.x + (xAdvance * bounceDistance) + (xAdvance * bounceDistance * 0.5), _position.y + (yAdvance * bounceDistance) + (yAdvance * bounceDistance * 0.5), xAdvance, yAdvance, bounceDistance * 0.25);
	
	_bouncing = true;
}

void Collectable::addBounceTween(float startX, float startY, float xAdvance, float yAdvance, float bounceDistance)
{
	CubicBezierCurve bounceTween;

	bounceTween.getP1().x = startX;
	bounceTween.getP1().y = startY;

	bounceTween.getP2().x = startX + (xAdvance * bounceDistance * 0.5);
	bounceTween.getP2().y = startY + (yAdvance * bounceDistance * 0.5) - (bounceDistance * 0.5);

	bounceTween.getP3().x = startX + (xAdvance * bounceDistance * 0.5);
	bounceTween.getP3().y = startY + (yAdvance * bounceDistance * 0.5) - (bounceDistance * 0.5);

	bounceTween.getP4().x = startX + (xAdvance * bounceDistance);
	bounceTween.getP4().y = startY + (yAdvance * bounceDistance);

	_bounceTweens.push_back(bounceTween);
}