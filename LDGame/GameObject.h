#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "SFML\Graphics.hpp"
#include "SpriteBatch.h"
#include "CollisionManager.h"

class SceneLayer;
class GameObject;

struct GameObjectToRemoveAndDeleteFlag
{
	public:
		GameObjectToRemoveAndDeleteFlag(GameObject* gameObject, bool deleteFlag)
		{
			_gameObject = gameObject;
			_deleteFlag = deleteFlag;
		}
		GameObject* getGameObject()
		{
			return _gameObject;
		}
		bool getDeleteFlag()
		{
			return _deleteFlag;
		}
	private:
		GameObject* _gameObject;
		bool _deleteFlag;
};

class GameObject
{
	public:
		GameObject();
		virtual ~GameObject();
		virtual void update(float deltaTime);
		virtual void render(SpriteBatch &spriteBatch, sf::Transform &transform);
		virtual void dispose();
		virtual void addChild(GameObject *gameObject);
		virtual bool removeChild(GameObject *gameObject, bool deleteObject);
		virtual void removeAllChildren(bool deleteObject, bool recursive);
		virtual void removeGameObjectsToBeRemoved();
		virtual void onAdded(SceneLayer *sceneLayer, GameObject *parent);
		virtual void onRemoved(bool deletingObject);
		void tranformPointParentCoordinates(GameObject *targetParent, Vector2<float> &point);
		SceneLayer *getSceneLayer();
		GameObject *getParent();
		std::vector<GameObject*> &getGameObjects();
	protected:
		std::vector<GameObject*> _gameObjects;
	private:
		SceneLayer *_sceneLayer;
		GameObject *_parent;
		std::vector<GameObjectToRemoveAndDeleteFlag> _gameObjectsToRemove;
};

#endif