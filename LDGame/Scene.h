#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "SFML\Graphics.hpp"
#include "SpriteBatch.h"
#include "SceneLayer.h"
#include "CollisionManager.h"

class GameObject;
class CollidableObject;
class SceneData;
class QuadTree;
class EventData;

class Scene : public SceneLayer
{
	public:
		Scene(SceneData *sceneData = 0);
		virtual ~Scene();
		virtual void onStart();
		virtual void onUpdate(float deltaTime);
		virtual void onRender();
		virtual void onDispose();
	protected:
		sf::Transform _transform;
	private:
		bool _firstTick;
		
};

#endif