#include "CurveBullet.h"
#include "Application.h"
#include "MathHelper.h"

CurveBullet::CurveBullet(GameScene &gameScene,
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
						 float amplitude,
						 float frequency,
						 std::map<std::string, std::vector<unsigned int>> animations,
						 const std::string &shootSoundURL,
						 const std::string &destroySoundURL)
						 : OmniDirectionBullet(gameScene,
											   collisionLayer,
											   filename,
											   textureAtlasName,
											   position,
											   xAdvance,
											   yAdvance,
											   speed,
											   lifetime,
											   bounceOffWalls,
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
							_currentCurveValue(0),
							CURVE_AMPLITUDE(amplitude * Application::zoom()),
							CURVE_FREQUENCY(frequency)
{
	setupCurve(xAdvance, yAdvance);
}

CurveBullet::~CurveBullet()
{
}

void CurveBullet::reset(Vector2<float> position, float xAdvance, float yAdvance)
{
	OmniDirectionBullet::reset(position, xAdvance, yAdvance);

	setupCurve(xAdvance, yAdvance);

	//reset curve offset values
	_currentCurveValue = 0;
	_currentOffset.x = 0;
	_currentOffset.y = 0;
}

void CurveBullet::setupCurve(float xAdvance, float yAdvance)
{
	Vector2<float> &p1 = _offsetCurve.getP1();
	Vector2<float> &p2 = _offsetCurve.getP2();
	Vector2<float> &p3 = _offsetCurve.getP3();
	Vector2<float> &p4 = _offsetCurve.getP4();

	p1.x = 0;
	p1.y = 0;

	p2.x = - (yAdvance * CURVE_AMPLITUDE);
	p2.y = (xAdvance * CURVE_AMPLITUDE);

	p3.x = (yAdvance * CURVE_AMPLITUDE);
	p3.y = - (xAdvance * CURVE_AMPLITUDE);

	p4.x = 0;
	p4.y = 0;

	//flip the curve for variety
	if(rand() % 2 == 0)
	{
		p2.x = -p2.x;
		p3.x = -p3.x;

		p2.y = -p2.y;
		p3.y = -p3.y;
	}
}

void CurveBullet::move(float deltaTime, float currentX, float currentY)
{
	_currentCurveValue += CURVE_FREQUENCY * deltaTime;
	if(_currentCurveValue > 1)
	{
		_currentCurveValue = 0;
	}

	Vector2<float> newOffset = _offsetCurve.getPoint(_currentCurveValue);
	setX(currentX + newOffset.x - _currentOffset.x);
	setY(currentY + newOffset.y - _currentOffset.y);
	_currentOffset = newOffset;

	OmniDirectionBullet::move(deltaTime, getX(), getY());

	_angle = MathHelper::getDegreesFromVector(getX() - currentX, getY() - currentY);
	setRotation(_angle);
}