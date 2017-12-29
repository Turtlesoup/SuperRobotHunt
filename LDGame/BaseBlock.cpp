#include "BaseBlock.h"
#include "Ray.h"
#include "Resources.h"

BaseBlock::BaseBlock(const Vector2<float>& position, GameScene& gameScene) : EmittingObject(SPRITE_PLAYER,
																							TEXTURE_ATLAS_SPRITES,
																							position,
																							75,
																							Vector2<float>(27,50),
																							sf::Color(255, 216, 0, 150),
																							200,
																							gameScene.underLightLayer(),
																							Vector2<float>(0, 0)),
																			 CollidableObject(COLLISION_LAYERS::LAYER_1),
																			 _gameScene(gameScene)
{
}

BaseBlock::~BaseBlock()
{
}

void BaseBlock::update(float deltaTime)
{
	EmittingObject::update(deltaTime);
}

void onCollision(CollidableObject* collidingObject)
{
	//do nothing
}

void onRayCollision(CollidableObject* collidingObject, Ray *ray, float rayIntersectionDistance)
{
	//do nothing
}