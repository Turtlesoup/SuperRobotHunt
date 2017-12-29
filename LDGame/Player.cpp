#include "Player.h"
#include "GameScene.h"
#include "SceneLayer.h"
#include "Light.h"
#include "Application.h"
#include "PlayerGun.h"
#include "Scene.h"
#include "Resources.h"
#include "Explosion.h"
#include "AudioManager.h"

Player::Player(const Vector2<float>& position, GameScene& gameScene) : EmittingObject(SPRITE_PLAYER,
																					  TEXTURE_ATLAS_SPRITES,
																					  position,
																					  75,
																					  Vector2<float>(27,50),
																					  sf::Color(255, 216, 0, 150),
																					  200,
																					  gameScene.underLightLayer(),
																					  Vector2<float>(0, 0)),
																	   CollidableObject(COLLISION_LAYERS::LAYER_1),
																	   _gameScene(gameScene),
																	   MAX_HEALTH(10),
																	   _health(MAX_HEALTH),
																	   _dead(false),
																	   ACCELERATION(0.05),
																	   MAX_SPEED(0.2),
																	   DECELERATION(0.025),
																	   _currentVelocityX(0),
																	   _currentVelocityY(0),
																	   _currentDirection(DIRECTION::RIGHT),
																	   BULLET_OFFSET_X_LEFT(-13.5),
																	   BULLET_OFFSET_X_RIGHT(13.5),
																	   BULLET_OFFSET_X_UP(-6.5),
																	   BULLET_OFFSET_X_DOWN(7.2),
																	   BULLET_OFFSET_Y_LEFT(12),
																	   BULLET_OFFSET_Y_RIGHT(10.5),
																	   BULLET_OFFSET_Y_UP(-10),
																	   BULLET_OFFSET_Y_DOWN(12.7),
																	   HIT_DELAY(500),
																	   _currentHitDelay(0),
																	   HIT_FORCE(0.15),
																	   _hitDirection(DIRECTION::UP)
{
	setCollisionBounds(Rect<int>(_position.x - (_width*0.5), _position.y - (_height*0.5), _width, _height));
	setCollidable(true);
	setCollisionChecking(true);
	setCollisionCheckingLayer(COLLISION_LAYERS::LAYER_2 | COLLISION_LAYERS::LAYER_4); //enemies, collectables

	_gun = new PlayerGun(GunProperties::createRandomProperties(), _gameScene);

	//setup animations for the player
	std::vector<unsigned int> frames;

	frames.push_back(0);
	addAnimation("idleLeft", frames);
	frames.clear();

	frames.push_back(1);
	addAnimation("idleDown", frames);
	frames.clear();

	frames.push_back(2);
	addAnimation("idleRight", frames);
	frames.clear();

	frames.push_back(3);
	addAnimation("idleUp", frames);
	frames.clear();

	frames.push_back(4);
	frames.push_back(5);
	frames.push_back(6);
	frames.push_back(7);
	addAnimation("walkLeft", frames);
	frames.clear();
	
	frames.push_back(8);
	frames.push_back(9);
	frames.push_back(10);
	frames.push_back(11);
	addAnimation("walkDown", frames);
	frames.clear();

	frames.push_back(12);
	frames.push_back(13);
	frames.push_back(14);
	frames.push_back(15);
	addAnimation("walkRight", frames);
	frames.clear();

	frames.push_back(16);
	frames.push_back(17);
	frames.push_back(18);
	frames.push_back(19);
	addAnimation("walkUp", frames);
	frames.clear();
}

Player::~Player()
{
}

void Player::moveUp(float deltaTime)
{
	_currentDirection = UP;
	_currentVelocityY -= ACCELERATION * deltaTime;
	if(_currentVelocityY < -MAX_SPEED)
	{
		_currentVelocityY = -MAX_SPEED;
	}
}

void Player::moveDown(float deltaTime)
{
	_currentDirection = DOWN;
	_currentVelocityY += ACCELERATION * deltaTime;
	if(_currentVelocityY > MAX_SPEED)
	{
		_currentVelocityY = MAX_SPEED;
	}
}

void Player::moveLeft(float deltaTime)
{
	_currentDirection = LEFT;
	_currentVelocityX -= ACCELERATION * deltaTime;
	if(_currentVelocityX < -MAX_SPEED)
	{
		_currentVelocityX = -MAX_SPEED;
	}
}

void Player::moveRight(float deltaTime)
{
	_currentDirection = RIGHT;
	_currentVelocityX += ACCELERATION * deltaTime;
	if(_currentVelocityX > MAX_SPEED)
	{
		_currentVelocityX = MAX_SPEED;
	}
}

void Player::shoot(float deltaTime)
{
	//compute the bullets position and angle
	Vector2<float> bulletPosition = _position;
	float angle = 0.0;
	switch(_currentDirection)
	{
		case DIRECTION::UP:
			angle = 270.0f;
			bulletPosition.x += BULLET_OFFSET_X_UP;
			bulletPosition.y += BULLET_OFFSET_Y_UP;
			break;
		case DIRECTION::DOWN:
			angle = 90.0f;
			bulletPosition.x += BULLET_OFFSET_X_DOWN;
			bulletPosition.y += BULLET_OFFSET_Y_DOWN;
			break;
		case DIRECTION::LEFT:
			angle = 180.0f;
			bulletPosition.x += BULLET_OFFSET_X_LEFT;
			bulletPosition.y += BULLET_OFFSET_Y_LEFT;
			break;
		case DIRECTION::RIGHT:
			angle = 0.0f;
			bulletPosition.x += BULLET_OFFSET_X_RIGHT;
			bulletPosition.y += BULLET_OFFSET_Y_RIGHT;
			break;
	}

	_gun->shoot(bulletPosition, angle);
}

void Player::update(float deltaTime)
{
	EmittingObject::update(deltaTime);

	//update collision bound position
	setCollisionBoundsLeft(_position.x - (_width*0.5));
	setCollisionBoundsTop(_position.y - (_height*0.5));

	if(_currentHitDelay > 0)
	{
		_currentHitDelay -= deltaTime;

		float hitForce = HIT_FORCE * (_currentHitDelay/HIT_DELAY) * deltaTime;

		switch(_hitDirection)
		{
			case DIRECTION::UP:
				setY(_position.y - hitForce);
				break;
			case DIRECTION::DOWN:
				setY(_position.y + hitForce);
				break;
			case DIRECTION::LEFT:
				setX(_position.x - hitForce);
				break;
			case DIRECTION::RIGHT:
				setX(_position.x + hitForce);
				break;
		}
	}

	std::string animationName;
	if(abs(_currentVelocityX) > 0.0 || abs(_currentVelocityY) > 0.0)
	{
		//move the player
		if(_currentVelocityX > 0.0)
		{
			setX(_position.x + (_currentVelocityX * deltaTime));
		}
		else if(_currentVelocityX < 0.0)
		{
			setX(_position.x - (-_currentVelocityX * deltaTime));
		}

		if(_currentVelocityY > 0.0)
		{
			setY(_position.y + (_currentVelocityY * deltaTime));
		}
		else if(_currentVelocityY < 0.0)
		{
			setY(_position.y - (-_currentVelocityY * deltaTime));
		}

		//set animation
		switch(_currentDirection)
		{
			case UP:
				animationName = "walkUp";
				break;
			case DOWN:
				animationName = "walkDown";
				break;
			case LEFT:
				animationName = "walkLeft";
				break;
			case RIGHT:
				animationName = "walkRight";
				break;
		}
	}
	else
	{
		//set animation
		switch(_currentDirection)
		{
			case UP:
				animationName = "idleUp";
				break;
			case DOWN:
				animationName = "idleDown";
				break;
			case LEFT:
				animationName = "idleLeft";
				break;
			case RIGHT:
				animationName = "idleRight";
				break;
		}
	}

	if(animationName != _currentAnimation)
	{
		_currentAnimation = animationName;
		play(animationName);
	}

	//reduce speed by deceleration
	if(_currentVelocityX >= DECELERATION)
	{
		_currentVelocityX -= DECELERATION * deltaTime;
		if(_currentVelocityX < DECELERATION)
		{
			_currentVelocityX = 0.0;
		}
	}
	else if(_currentVelocityX <= -DECELERATION)
	{
		_currentVelocityX += DECELERATION * deltaTime;
		if(_currentVelocityX > -DECELERATION)
		{
			_currentVelocityX = 0.0;
		}
	}

	if(_currentVelocityY >= DECELERATION)
	{
		_currentVelocityY -= DECELERATION * deltaTime;
		if(_currentVelocityY < DECELERATION)
		{
			_currentVelocityY = 0.0;
		}
	}
	else if(_currentVelocityY <= -DECELERATION)
	{
		_currentVelocityY += DECELERATION * deltaTime;
		if(_currentVelocityY > -DECELERATION)
		{
			_currentVelocityY = 0.0;
		}
	}

	//bounds check for game area
	if(_position.x < _gameScene.getScreenBoundsMinX() + (_width*0.5))
	{
		_position.x = _gameScene.getScreenBoundsMinX() + (_width*0.5);
	}
	else if(_position.x > _gameScene.getScreenBoundsMaxX() - (_width*0.5))
	{
		_position.x = _gameScene.getScreenBoundsMaxX() - (_width*0.5);
	}

	if(_position.y < _gameScene.getScreenBoundsMinY())
	{
		_position.y = _gameScene.getScreenBoundsMinY();
	}
	else if(_position.y > _gameScene.getScreenBoundsMaxY() - (_height*0.5))
	{
		_position.y = _gameScene.getScreenBoundsMaxY() - (_height*0.5);
	}
}

void Player::onCollision(CollidableObject* collidingObject)
{
}

void Player::onRayCollision(CollidableObject* collidingObject, Ray *ray, float rayIntersectionDistance)
{
}

void Player::hit(float xDirection, float yDirection, float power)
{
	if(_currentHitDelay <= 0)
	{
		//set hit delay and direction of hit
		_currentHitDelay = HIT_DELAY;
		_hitDirection = Directions::valuesToDirection(xDirection, yDirection);

		//reduce the player's health by the power of the hit
		_health -= power;

		//update the hud
		_gameScene.updateHUD();

		//play the hit sfx
		AudioManager::Get()->playSound(AUDIO_PLAYER_HIT);

		//if the player's health reaches 0 then the player is destroyed
		if(_health <= 0)
		{
			destroy();
		}
	}
}

void Player::destroy()
{	
	_dead = true;

	//create the explosion object
	_gameScene.overObjectsLayer()->addChild(new Explosion(_position, _gameScene));

	//set the player invisible
	setVisible(false);

	_gameScene.onPlayerDestroyed();
}

void Player::onAdded(SceneLayer *sceneLayer, GameObject *parent)
{
	EmittingObject::onAdded(sceneLayer, parent);
	_gameScene.overObjectsLayer()->addChild(_gun);
}

void Player::onRemoved(bool deletingObject)
{
	EmittingObject::onRemoved(deletingObject);
	_gameScene.overObjectsLayer()->removeChild(_gun, deletingObject);
}

void Player::addHealth(float value)
{
	_health += value;
	if(_health > MAX_HEALTH)
	{
		_health = MAX_HEALTH;
	}

	_gameScene.updateHUD();
}

float Player::currentHealthPercentage()
{
	return _health / MAX_HEALTH;
}

bool Player::isDead()
{
	return _dead;
}

void Player::setGunProperties(GunProperties gunProperties)
{
	_gun->setProperties(gunProperties);
}