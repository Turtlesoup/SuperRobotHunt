#include "LaserBullet.h"
#include "MathHelper.h"
#include "Application.h"
#include "CircleFlash.h"
#include "FlickeringLight.h"

LaserBullet::LaserBullet(GameScene &gameScene,
						 COLLISION_LAYERS collisionLayer,
						 const std::string &bodyFilename,
						 const std::string &startFilename,
						 const std::string &endFilename,
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
						 : BaseBullet(gameScene,
									  collisionLayer,
									  bodyFilename,
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
							MAX_LASER_DISTANCE(sqrt((double)((Application::screenWidth() * Application::screenWidth()) + (Application::screenHeight() * Application::screenHeight()))))
{
	setVisible(false);

	CollisionManager::Get()->addRayCastCheck(this, _position, Vector2<float>(_xAdvance, _yAdvance), _collisionLayer, MAX_LASER_DISTANCE, 1);

	bulletStart = new AnimatedDisplayObject(startFilename, textureAtlasName, Vector2<float>(), animationSpeed, spriteDimensions);
	bulletEnd = new AnimatedDisplayObject(endFilename, textureAtlasName, Vector2<float>(), animationSpeed, spriteDimensions);

	//add the animations to bullet end
	std::map<std::string, std::vector<unsigned int>>::const_iterator animationsIterator, animationsEnd;
	animationsEnd = animations.end();
	for(animationsIterator = animations.begin(); animationsIterator != animationsEnd; ++animationsIterator)
	{
		bulletStart->addAnimation((*animationsIterator).first, (*animationsIterator).second);
		bulletEnd->addAnimation((*animationsIterator).first, (*animationsIterator).second);
	}
}

LaserBullet::~LaserBullet()
{
}

void LaserBullet::reset(Vector2<float> position, float xAdvance, float yAdvance)
{
	BaseBullet::reset(position, xAdvance, yAdvance);

	setVisible(false);

	CollisionManager::Get()->addRayCastCheck(this, _position, Vector2<float>(_xAdvance, _yAdvance), _collisionLayer, MAX_LASER_DISTANCE, 1);
}

void LaserBullet::shootLaser(const Vector2<float> &direction, const Vector2<float> &origin, float length)
{
	float angle = MathHelper::getDegreesFromVector(direction);

	setWidth(length);
	setRotation(angle);

	setX(origin.x + (length * direction.x * 0.5));
	setY(origin.y + (length * direction.y * 0.5));

	bulletStart->setRotation(angle);
	bulletStart->setX(origin.x - direction.x);
	bulletStart->setY(origin.y - direction.y);

	bulletEnd->setRotation(angle);
	bulletEnd->setX(origin.x + (length * direction.x));
	bulletEnd->setY(origin.y + (length * direction.y));

	getTint().a = 0xFF;

	destroy();

	setVisible(true);

	//scale and rotate the light correctly for the laser
	float lightLength;
	if(length == MAX_LASER_DISTANCE)
	{
		lightLength = MAX_LASER_DISTANCE * 1.25;
	}
	else
	{
		lightLength = length * 1.75;
	}
	_light->setWidth(lightLength);
	_light->setHeight(100);
	_light->setRotation(angle);

	//spawn flashes along the laser line
	CircleFlash *laserFlash;

	//spawn a small circular flash effect at the start of the laser
	laserFlash = new CircleFlash(origin, _gameScene, false, sf::Color(255, 255, 255, 255), 0.25);
	_gameScene.overObjectsLayer()->addChild(laserFlash);

	//spawn a circular flash effect at the end point of the laser
	laserFlash = new CircleFlash(Vector2<float>(origin.x + (direction.x * length), origin.y + (direction.y * length)), _gameScene, true, sf::Color(255, 255, 255, 255), 0.5);
	_gameScene.overObjectsLayer()->addChild(laserFlash);
}

void LaserBullet::update(float deltaTime)
{
	BaseBullet::update(deltaTime);
}

void LaserBullet::destroy()
{
	BaseBullet::destroy();
}

void LaserBullet::playDestroyAnimation()
{
	play("explode");
	bulletStart->play("explode");
	bulletEnd->play("explode");
}

void LaserBullet::onRayCollision(CollidableObject* collidingObject, Ray *ray, float rayIntersectionDistance)
{
	float laserLength = rayIntersectionDistance;
	if(laserLength == FLT_MAX)
	{
		laserLength = MAX_LASER_DISTANCE;
	}
	else if(laserLength == 0)
	{
		laserLength = 1;
	}

	Vector2<float> rayOrigin = ray->origin();
	Vector2<float> rayDirection = ray->direction();

	if(collidingObject != nullptr)
	{
		//inform the parent gun object that the bullet has collided with an object
		//the gun will determine whether this collision is valid (e.g. enemy bullets
		//shouldn't collide with other enemies)
		Vector2<float> direction = ray->direction();
		_onBulletHitCallback(this, direction.x, direction.y, collidingObject);

		//we want to make the laser shoot to the center of the target object
		//rather than the collision boundary edge, so we want to add some extra
		//length to the overall length of the laser depending on the magnitude of
		//its x and y components.
		Rect<int> collisionObjectBounds = collidingObject->getCollisionBounds();
		if(rayDirection.x >= rayDirection.y)
		{
			laserLength += collisionObjectBounds.width*0.5;
		}
		else if(rayDirection.x < rayDirection.y)
		{
			laserLength += collisionObjectBounds.height*0.5;
		}
	}

	shootLaser(ray->direction(), ray->origin(), laserLength);
}

void LaserBullet::onAdded(SceneLayer *sceneLayer, GameObject *parent)
{
	BaseBullet::onAdded(sceneLayer, parent);

	parent->addChild(bulletStart);
	parent->addChild(bulletEnd);
}

void LaserBullet::onRemoved(bool deletingObject)
{
	getParent()->removeChild(bulletStart, true);
	getParent()->removeChild(bulletEnd, true);

	BaseBullet::onRemoved(deletingObject);
}