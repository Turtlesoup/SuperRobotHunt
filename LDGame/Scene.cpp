#include <algorithm>
#include "SceneData.h"
#include "GameObject.h"
#include "DisplayObject.h"
#include "TextDisplayObject.h"
#include "CollidableObject.h"
#include "SceneLayer.h"
#include "QuadTree.h"
#include "Scene.h"
#include "Application.h"

Scene::Scene(SceneData *sceneData) : SceneLayer(sf::BlendAlpha),
								     _firstTick(false),
									 _transform(sf::Transform::Identity)
{
	//apply the scene zoom
	setScale(Application::zoom(), Application::zoom());
}

Scene::~Scene()
{
}

void Scene::onStart()
{ 
}

void Scene::onUpdate(float deltaTime)
{
	//update the display
	SceneLayer::update(deltaTime);

	//check for collisions
	CollisionManager::Get()->checkCollisions();

	//remove the game objects that have been set to be removed
	removeGameObjectsToBeRemoved();
}

void Scene::onRender()
{
	_transform.translate(_position.x - _origin.x, _position.y - _origin.y).rotate(_angle, _origin.x, _origin.y).scale(_scale.x, _scale.y, _origin.x, _origin.y);

	SceneLayer::render(_spriteBatch, _transform);

	_transform.scale(1/_scale.x, 1/_scale.y, _origin.x, _origin.y).rotate(-_angle, _origin.x, _origin.y).translate(-_position.x + _origin.x, -_position.y + _origin.y);
}

void Scene::onDispose()
{
	GameObject::dispose();
}