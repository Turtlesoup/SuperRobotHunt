#ifndef BASE_BULLET_H
#define BASE_BULLET_H

#include "GameScene.h"
#include "EmittingObject.h"
#include "CollidableObject.h"
#include "CollisionLayers.h"
#include "Gun.h"

#include <functional>
#include <map>
#include <string>
#include <vector>

class SceneLayer;

class BaseBullet : public EmittingObject, public CollidableObject
{
	public:
		BaseBullet(GameScene &gameScene,
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
				   const std::string &destroySoundURL);
		virtual ~BaseBullet();
		virtual void shoot();
		virtual void reset(Vector2<float> position, float xAdvance, float yAdvance);
		bool isDead();
		virtual void update(float deltaTime);
		void setBulletHitCallback(const std::function<bool(BaseBullet*, float, float, CollidableObject*)> &onBulletHitCallback);
		void setReuseBullet(bool value);
		float power();
	protected:
		virtual void onCollision(CollidableObject* collidingObject);
		virtual void onRayCollision(CollidableObject* collidingObject, Ray *ray, float rayIntersectionDistance);
		virtual void playIdleAnimation();
		virtual void playDestroyAnimation();
		virtual void destroy();
		void onDestroyAnimationComplete();
		GameScene &_gameScene;
		COLLISION_LAYERS _collisionLayer;
		std::function<bool(BaseBullet*, float, float, CollidableObject*)> _onBulletHitCallback;
		bool _reuseBullet;
		float SPEED;
		float _xAdvance;
		float _yAdvance;
		bool _dead;
		bool _destroying;
		const float BULLET_SIZE;
		float POWER;
		const std::string SHOOT_SOUND_URL;
		const std::string DESTROY_SOUND_URL;
		float LIFETIME;
		float _currentLifeTime;
};

#endif