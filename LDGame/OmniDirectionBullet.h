#ifndef OMNI_DIRECTION_BULLET_H
#define OMNI_DIRECTION_BULLET_H

#include "BaseBullet.h"
#include "Directions.h"

class SceneLayer;

class OmniDirectionBullet : public BaseBullet
{
	public:
		OmniDirectionBullet(GameScene &gameScene,
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
							const std::string &destroySoundURL);
		virtual ~OmniDirectionBullet();
		virtual void reset(Vector2<float> position, float xAdvance, float yAdvance);
		virtual void update(float deltaTime);
		void setDoRayCastCheckOnBulletTravelPath(bool value);
	protected:
		virtual void move(float deltaTime, float currentX, float currentY);
		virtual void destroy();
		virtual void playIdleAnimation();
		virtual void playDestroyAnimation();
		float _angle;
	private:
		bool _doRayCastCheckOnBulletTravelPath;
		bool _bounceOffWalls;
};

#endif