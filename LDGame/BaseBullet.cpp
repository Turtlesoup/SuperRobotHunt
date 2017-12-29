#include "BaseBullet.h"
#include "Application.h"
#include "SceneLayer.h"
#include "Light.h"
#include "MathHelper.h"
#include "AudioManager.h"

BaseBullet::BaseBullet(GameScene &gameScene,
					   COLLISION_LAYERS collisionLayer,
					   const std::string &filename,
					   const std::string &textureAtlasName,
					   const Vector2<float> &position,
					   float xAdvance,
					   float yAdvance,
					   float speed,
					   float lifetime,
					   float power,
					   float bulletSize,
					   float animationSpeed,
					   Vector2<float> spriteDimensions,
					   const sf::Color& lightColour,
					   float lightSize,
					   SceneLayer* lightSceneLayer,
					   Vector2<float> lightOffset,
					   std::map<std::string, std::vector<unsigned int>> animations,
					   const std::string &shootSoundURL,
					   const std::string &destroySoundURL)
					   : EmittingObject(filename, textureAtlasName, position, animationSpeed, spriteDimensions, lightColour, lightSize, lightSceneLayer, lightOffset),
						 CollidableObject(),
						 _gameScene(gameScene),
						 _collisionLayer(collisionLayer),
						 _reuseBullet(false),
						 _dead(false),
						 _destroying(false),
						 SPEED(speed),
						 BULLET_SIZE(bulletSize),
						 _xAdvance(xAdvance),
						 _yAdvance(yAdvance),
						 POWER(power),
						 SHOOT_SOUND_URL(shootSoundURL),
						 DESTROY_SOUND_URL(destroySoundURL),
						 LIFETIME(lifetime),
						 _currentLifeTime(LIFETIME)
{
	setCollisionBounds(Rect<int>(_position.x - (BULLET_SIZE*0.5), _position.y - (BULLET_SIZE*0.5), BULLET_SIZE, BULLET_SIZE));
	setCollidable(true);

	//add the animations
	std::map<std::string, std::vector<unsigned int>>::const_iterator animationsIterator, animationsEnd;
	animationsEnd = animations.end();
	for(animationsIterator = animations.begin(); animationsIterator != animationsEnd; ++animationsIterator)
	{
		addAnimation((*animationsIterator).first, (*animationsIterator).second);
	}
}

BaseBullet::~BaseBullet()
{
}

void BaseBullet::shoot()
{
	playIdleAnimation();
	AudioManager::Get()->playSound(SHOOT_SOUND_URL);
}

void BaseBullet::reset(Vector2<float> position, float xAdvance, float yAdvance)
{
	setX(position.x);
	setY(position.y);
	_xAdvance = xAdvance;
	_yAdvance = yAdvance;
	_dead = false;
	_destroying = false;
	_currentLifeTime = LIFETIME;
	removeOnAnimationCompleteCallback();
	setVisible(true);
	setCollidable(true);
	setCollisionChecking(false);

	shoot();
}

bool BaseBullet::isDead()
{
	return _dead;
}

void BaseBullet::destroy()
{
	if(!_destroying)
	{
		setCollidable(false);
		setCollisionChecking(false);
		addOnAnimationCompleteCallback(std::bind<void>(&BaseBullet::onDestroyAnimationComplete, this));
		playDestroyAnimation();
		AudioManager::Get()->playSound(DESTROY_SOUND_URL);
		_destroying = true;
	}
}

void BaseBullet::playIdleAnimation()
{
	//do nothing
}

void BaseBullet::playDestroyAnimation()
{
	//do nothing
}

void BaseBullet::onDestroyAnimationComplete()
{
	removeOnAnimationCompleteCallback();
	stop();
	_dead = true;

	//if the parent gun is null then we need to
	//dispose the bullet as it wont be reused.
	//otherwise just hide the bullet until it is
	//reused by the gun.
	if(_reuseBullet)
	{
		setVisible(false);
	}
	else
	{
		getSceneLayer()->removeChild(this, true);
	}
}

void BaseBullet::update(float deltaTime)
{
	EmittingObject::update(deltaTime);

	_currentLifeTime -= deltaTime;
	if(_currentLifeTime <= 0)
	{
		destroy();
	}
}


void BaseBullet::setBulletHitCallback(const std::function<bool(BaseBullet*, float, float, CollidableObject*)> &onBulletHitCallback)
{
	_onBulletHitCallback = onBulletHitCallback;
}

void BaseBullet::onCollision(CollidableObject* collidingObject)
{
	//inform the parent gun object that the bullet has collided with an object
	//the gun will determine whether this collision is valid (e.g. enemy bullets
	//shouldn't collide with other enemies)
	bool destroyBullet = _onBulletHitCallback(this, _xAdvance, _yAdvance, collidingObject);

	if(destroyBullet)
	{
		//destroy the bullet
		destroy();
	}
}

void BaseBullet::onRayCollision(CollidableObject* collidingObject, Ray *ray, float rayIntersectionDistance)
{
	if(collidingObject != nullptr)
	{
		//inform the parent gun object that the bullet has collided with an object
		//the gun will determine whether this collision is valid (e.g. enemy bullets
		//shouldn't collide with other enemies)
		Vector2<float> direction = ray->direction();
		bool destroyBullet = _onBulletHitCallback(this, direction.x, direction.y, collidingObject);

		if(destroyBullet)
		{
			//destroy the bullet
			destroy();
		}
	}
}

void BaseBullet::setReuseBullet(bool value)
{
	_reuseBullet = value;
}

float BaseBullet::power()
{
	return POWER;
}