#ifndef CURVE_BULLET_H
#define CURVE_BULLET_H

#include "OmniDirectionBullet.h"
#include "CubicBezierCurve.h"

class CurveBullet : public OmniDirectionBullet
{
	public:
		CurveBullet(GameScene &gameScene,
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
				    const std::string &destroySoundURL);
		virtual ~CurveBullet();
		virtual void reset(Vector2<float> position, float xAdvance, float yAdvance);
	protected:
		virtual void move(float deltaTime, float currentX, float currentY);
		void setupCurve(float xAdvance, float yAdvance);
		CubicBezierCurve _offsetCurve;
		Vector2<float> _currentOffset;
		float _currentCurveValue;
		const float CURVE_AMPLITUDE;
		const float CURVE_FREQUENCY;
};

#endif