#include "OmniDirectionBullet.h"
#include "Application.h"
#include "SceneLayer.h"
#include "Light.h"
#include "MathHelper.h"

OmniDirectionBullet::OmniDirectionBullet(GameScene &gameScene,
										 COLLISION_LAYERS collisionLayer,
										 const std::string &filename,
									     const std::string &textureAtlasName,
									     const Vector2<float> &position,
									     float xAdvance,
										 float yAdvance,
									     float speed,
										 float lifetime,
										 bool bounceOffWalls,
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
									     : BaseBullet(gameScene,
													  collisionLayer,
													  filename,
													  textureAtlasName,
													  position,
													  xAdvance,
													  yAdvance,
													  speed,
													  lifetime,
													  power,
													  bulletSize,
													  animationSpeed,
													  spriteDimensions,
													  lightColour,
													  lightSize,
													  lightSceneLayer,
													  lightOffset,
													  animations,
													  shootSoundURL,
													  destroySoundURL),
											_doRayCastCheckOnBulletTravelPath(false),
											_bounceOffWalls(bounceOffWalls)
{
	_angle = MathHelper::getDegreesFromVector(_xAdvance, _yAdvance);
	setRotation(_angle);
}

OmniDirectionBullet::~OmniDirectionBullet()
{
}

void OmniDirectionBullet::reset(Vector2<float> position, float xAdvance, float yAdvance)
{
	BaseBullet::reset(position, xAdvance, yAdvance);

	_angle = MathHelper::getDegreesFromVector(_xAdvance, _yAdvance);
	setRotation(_angle);
}

void OmniDirectionBullet::update(float deltaTime)
{
	BaseBullet::update(deltaTime);

	if(!_dead && !_destroying)
	{
		float currentX = getX();
		float currentY = getY();

		if(_bounceOffWalls)
		{
			if(currentX < _gameScene.getScreenBoundsMinX() + (BULLET_SIZE * 0.5))
			{
				currentX = _gameScene.getScreenBoundsMinX() + BULLET_SIZE;
				_xAdvance = -_xAdvance;
			}
			else if(currentX > _gameScene.getScreenBoundsMaxX() - (BULLET_SIZE * 0.5))
			{
				currentX = _gameScene.getScreenBoundsMaxX() - (BULLET_SIZE * 0.5);
				_xAdvance = -_xAdvance;
			}

			if(currentY < _gameScene.getScreenBoundsMinY() + (BULLET_SIZE * 0.5))
			{
				currentY = _gameScene.getScreenBoundsMinY() + (BULLET_SIZE * 0.5);
				_yAdvance = -_yAdvance;
			}
			else if(currentY > _gameScene.getScreenBoundsMaxY() - (BULLET_SIZE * 0.5))
			{
				currentY = _gameScene.getScreenBoundsMaxY() - (BULLET_SIZE * 0.5);
				_yAdvance = -_yAdvance;
			}
		}
		else if(currentY < _gameScene.getScreenBoundsMinY() + BULLET_SIZE || currentY > _gameScene.getScreenBoundsMaxY() - BULLET_SIZE || currentX < _gameScene.getScreenBoundsMinX() + BULLET_SIZE || currentX > _gameScene.getScreenBoundsMaxX() - BULLET_SIZE)
		{
			destroy();
		}

		if(!_destroying)
		{
			move(deltaTime, currentX, currentY);

			//update collision bound position
			setCollisionBoundsLeft(_position.x - (_width*0.5));
			setCollisionBoundsTop(_position.y - (_height*0.5));
		}
	}
}

void OmniDirectionBullet::move(float deltaTime, float currentX, float currentY)
{
	float speed = SPEED * deltaTime;

	//if the doRayCastCheckOnBulletTravelPath flag is set to true then we want to cast a ray behind the bullet
	//that checks for collisions along the bullets path between this update and the last and collides with objects
	//that are hit by the ray. This is useful for fast moving bullets that are likely to "jump" colliding with enemies
	//between update loops.
	if(_doRayCastCheckOnBulletTravelPath)
	{
		CollisionManager::Get()->addRayCastCheck(this, Vector2<float>(currentX, currentY), Vector2<float>(_xAdvance, _yAdvance), _collisionLayer, speed, 1);
	}

	setX(currentX + (speed * _xAdvance));
	setY(currentY + (speed * _yAdvance));
}

void OmniDirectionBullet::setDoRayCastCheckOnBulletTravelPath(bool value)
{
	_doRayCastCheckOnBulletTravelPath = value;
}

void OmniDirectionBullet::playIdleAnimation()
{
	play("idle");
}

void OmniDirectionBullet::playDestroyAnimation()
{
	play("explode");
}

void OmniDirectionBullet::destroy()
{
	if(!_destroying)
	{
		setCollidable(false);
		setCollisionChecking(false);
	}

	BaseBullet::destroy();
}