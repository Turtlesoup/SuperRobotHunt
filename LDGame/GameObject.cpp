#include "Game.h"
#include "GameObject.h"
#include "SceneLayer.h"
#include "CollidableObject.h"
#include "SpriteDisplayObject.h"
#include "TextDisplayObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::update(float deltaTime)
{
	CollisionManager *collisionManager = CollisionManager::Get();
	CollidableObject *collidableObject;

	//clone the game objects array so objects added by other objects being updated do not affect the loop
	std::vector<GameObject*> gameObjects(_gameObjects);
	std::vector<GameObject*>::iterator gameObjectsIterator, gameObjectsIteratorEnd;
	for(gameObjectsIterator = gameObjects.begin(), gameObjectsIteratorEnd = gameObjects.end(); gameObjectsIterator != gameObjectsIteratorEnd; ++ gameObjectsIterator)
	{
		(*gameObjectsIterator)->update(deltaTime);

		//if the game object is a collidable object and collision for the object is set then add to the quadtree
		collidableObject = dynamic_cast<CollidableObject*>(*gameObjectsIterator);
		if(collidableObject != 0)
		{
			collisionManager->addCollidableObject(collidableObject);
		}
	}
}

void GameObject::render(SpriteBatch &spriteBatch, sf::Transform &transform)
{
	std::vector<GameObject*>::iterator gameObjectsIterator, gameObjectsIteratorEnd;
	for(gameObjectsIterator = _gameObjects.begin(), gameObjectsIteratorEnd = _gameObjects.end(); gameObjectsIterator != gameObjectsIteratorEnd; ++ gameObjectsIterator)
	{
		(*gameObjectsIterator)->render(spriteBatch, transform);
	}
}

void GameObject::dispose()
{
	//remove and delete all immediate children
	removeAllChildren(true, true);
	removeGameObjectsToBeRemoved();
}

void GameObject::addChild(GameObject *gameObject)
{
	_gameObjects.push_back(gameObject);

	//call the on added function of the object
	gameObject->onAdded(getSceneLayer(), this);
}

bool GameObject::removeChild(GameObject *gameObject, bool deleteObject)
{
	//if the object exists in this layer then set it to be removed if we havent already done so
	//if the object doesnt exist in this layer then recursively check the display layers for the
	//object and assign it to be deleted once found

	std::vector<GameObject*>::iterator gameObjectsIterator, gameObjectsBegin, gameObjectsEnd;

	gameObjectsBegin = _gameObjects.begin();
	gameObjectsEnd = _gameObjects.end();
	gameObjectsIterator = std::find(gameObjectsBegin, gameObjectsEnd, gameObject);

	if(gameObjectsIterator != _gameObjects.end())
	{
		//if the game object isnt already added to the list of game objects to remove then add it
		std::vector<GameObjectToRemoveAndDeleteFlag>::iterator gameObjectsToRemoveIterator, gameObjectsToRemoveIteratorEnd;
		for(gameObjectsToRemoveIterator = _gameObjectsToRemove.begin(), gameObjectsToRemoveIteratorEnd = _gameObjectsToRemove.end(); gameObjectsToRemoveIterator != gameObjectsToRemoveIteratorEnd; ++ gameObjectsToRemoveIterator)
		{
			GameObjectToRemoveAndDeleteFlag gameObjectToRemoveAndDeleteFlag = (*gameObjectsToRemoveIterator);
			if(gameObjectToRemoveAndDeleteFlag.getGameObject() == gameObject)
			{
				//return true as the objects already exists in the removal list but we have found the object
				return true;
			}
		}

		//add the object to the list of objects to be removed after the current update cycle completes
		_gameObjectsToRemove.push_back(GameObjectToRemoveAndDeleteFlag(gameObject, deleteObject));
		gameObject->onRemoved(deleteObject);

		//return that the object to remove was found
		return true;
	}
	else
	{
		for(gameObjectsIterator = gameObjectsBegin; gameObjectsIterator != gameObjectsEnd; ++ gameObjectsIterator)
		{
			//remove the object from the display layers recursively
			//if the call returns true then the object to remove was
			//found in one of the children and so we dont need to continue
			//checking.
			if((*gameObjectsIterator)->removeChild(gameObject, deleteObject))
			{
				return true;
			}
		}
	}

	//the object was not found
	return false;
}

void GameObject::removeAllChildren(bool deleteObject, bool recursive)
{
	//iterate through all the children game objects and remove them
	GameObject *gameObject;
	std::vector<GameObject*>::iterator gameObjectsIterator, gameObjectsBegin, gameObjectsEnd;
	gameObjectsBegin = _gameObjects.begin();
	gameObjectsEnd = _gameObjects.end();
	for(gameObjectsIterator = gameObjectsBegin; gameObjectsIterator != gameObjectsEnd; ++ gameObjectsIterator)
	{
		//remove the child's children if the recursive flag is set
		if(recursive)
		{
			(*gameObjectsIterator)->removeAllChildren(deleteObject, true);
		}

		//remove the child
		removeChild((*gameObjectsIterator), deleteObject);
	}
}

void GameObject::removeGameObjectsToBeRemoved()
{
	//for each child game object, remove the game objects to be removed from the layers
	std::vector<GameObject*>::const_iterator gameObjectsIterator, gameObjectsEnd;
	DisplayObject* displayObject;

	for(gameObjectsIterator = _gameObjects.begin(), gameObjectsEnd = _gameObjects.end(); gameObjectsIterator != gameObjectsEnd; ++ gameObjectsIterator)
	{
		(*gameObjectsIterator)->removeGameObjectsToBeRemoved();
	}

	//remove the game objects contained within this object that are set to be removed
	std::vector<GameObjectToRemoveAndDeleteFlag>::iterator gameObjectsToRemoveIterator, gameObjectsToRemoveEnd;
	GameObject* gameObject;
	bool deleteFlag;
	
	for(gameObjectsToRemoveIterator = _gameObjectsToRemove.begin(), gameObjectsToRemoveEnd = _gameObjectsToRemove.end(); gameObjectsToRemoveIterator != gameObjectsToRemoveEnd; ++ gameObjectsToRemoveIterator)
	{
		GameObjectToRemoveAndDeleteFlag gameObjectToRemoveAndDeleteFlag = (*gameObjectsToRemoveIterator);
		
		gameObject = gameObjectToRemoveAndDeleteFlag.getGameObject();
		deleteFlag = gameObjectToRemoveAndDeleteFlag.getDeleteFlag();

		//find and remove the game object
		gameObjectsIterator = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
		_gameObjects.erase(gameObjectsIterator);

		//if there delete flag was set then delete the object
		if(deleteFlag)
		{
			gameObject->dispose();
			delete gameObject;
		}
	}

	//clear the objects to remove vector
	_gameObjectsToRemove.clear();
}

void GameObject::onAdded(SceneLayer *sceneLayer, GameObject *parent)
{
	_sceneLayer = sceneLayer;
	_parent = parent;
}

void GameObject::onRemoved(bool deletingObject)
{
}

std::vector<GameObject*> &GameObject::getGameObjects()
{
	return _gameObjects;
}

SceneLayer *GameObject::getSceneLayer()
{
	return _sceneLayer;
}

GameObject *GameObject::getParent()
{
	return _parent;
}

void GameObject::tranformPointParentCoordinates(GameObject *targetParent, Vector2<float> &point)
{
	//obtain the parents up to the target parent that are transformable objects
	GameObject *currentParent = this;
	TransformableObject *transformableObject;
	std::vector<TransformableObject*> transformableParents;

	while(currentParent != nullptr)
	{
		transformableObject = dynamic_cast<TransformableObject*>(currentParent);
		if(transformableObject != nullptr)
		{
			transformableParents.push_back(transformableObject);
		}

		if(currentParent == targetParent)
		{
			break;
		}

		currentParent = currentParent->getParent();
	}

	//working backwards from the uppermost parent to the child, apply the transform to the point
	sf::Transform transform = sf::Transform::Identity;

	std::vector<TransformableObject*>::reverse_iterator transformableParentsReverseIterator, transformableParentsReverseBegin, transformableParentsReverseEnd;
	transformableParentsReverseBegin = transformableParents.rbegin();
	transformableParentsReverseEnd = transformableParents.rend();
	Vector2<float> origin;
	Vector2<float> scale;
	for(transformableParentsReverseIterator = transformableParentsReverseBegin; transformableParentsReverseIterator != transformableParentsReverseEnd; ++ transformableParentsReverseIterator)
	{
		transformableObject = (*transformableParentsReverseIterator);
		origin = transformableObject->getOrigin();
		scale = transformableObject->getScale();
		transform.translate(transformableObject->getX() - origin.x, transformableObject->getY() - origin.y).rotate(transformableObject->getRotation(), origin.x, origin.y).scale(scale.x, scale.y, origin.x, origin.y);
	}

	const float* matrix = transform.getMatrix();
    float pX = point.x;
    float pY = point.y;
    point.x = (matrix[0] * pX) + (matrix[4] * pY) + matrix[12];
    point.y = (matrix[1] * pX) + (matrix[5] * pY) + matrix[13];
}