#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "EmittingObject.h"
#include "CollidableObject.h"
#include "Directions.h"
#include "GameScene.h"
#include "CubicBezierCurve.h"

class Collectable : public EmittingObject, public CollidableObject
{
	public:
		Collectable(const Vector2<float> &position, GameScene& gameScene, std::string filename, Vector2<float> spriteDimensions, float collectableSize, sf::Color lightColour, float lightSize);
		virtual ~Collectable();
		virtual void update(float deltaTime);
		virtual void onCollected(Player *player);
		virtual void onCollision(CollidableObject *collidingObject);
		virtual void onRayCollision(CollidableObject *collidingObject, Ray *ray, float rayIntersectionDistance);
		virtual void doBounceAnimation();
	protected:
		GameScene& _gameScene;
	private:
		void playCollectAnimation();
		void onCollectAnimationComplete();
		void addBounceTween(float startX, float startY, float xAdvance, float yAdvance, float bounceDistance);
		bool _collecting;
		const float COLLECTABLE_SIZE;
		bool _bouncing;
		const float MIN_BOUNCE_DISTANCE;
		const float MAX_BOUNCE_DISTANCE;
		const float BOUNCE_SPEED;
		const float TIME_BEFORE_REMOVAL_FLICKER;
		const float TIME_BEFORE_REMOVAL;
		const float FLICKER_TIME;
		std::vector<CubicBezierCurve> _bounceTweens;
		unsigned int _currentBounceTweenIndex;
		float _currentCurveValue;
		float _currentRemovalTime;
		float _currentFlickerTime;
};

#endif