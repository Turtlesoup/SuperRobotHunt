#ifndef LASER_BULLET_H
#define LASER_BULLET_H

#include "BaseBullet.h"

class LaserBullet : public BaseBullet
{
	public:
		LaserBullet(GameScene &gameScene,
					COLLISION_LAYERS collisionLayer,
					const std::string &bodyFilename,
					const std::string &startFilename,
					const std::string &endFilename,
					const std::string &textureAtlasName,
					const Vector2<float> &position,
					float xAdvance,
					float yAdvance,
					float speed,
					float power,
					float lifetime,
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
		virtual ~LaserBullet();
		virtual void reset(Vector2<float> position, float xAdvance, float yAdvance);
		virtual void shootLaser(const Vector2<float> &direction, const Vector2<float> &origin, float length);
		virtual void update(float deltaTime);
		virtual void onRayCollision(CollidableObject* collidingObject, Ray *ray, float rayIntersectionDistance);
		void onAdded(SceneLayer *sceneLayer, GameObject *parent);
		void onRemoved(bool deletingObject);
	protected:
		virtual void destroy();
		virtual void playDestroyAnimation();
		const float MAX_LASER_DISTANCE;
		AnimatedDisplayObject *bulletStart;
		AnimatedDisplayObject *bulletEnd;
};

#endif