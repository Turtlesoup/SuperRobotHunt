#include "QuadTree.h"
#include "CollidableObject.h"
#include <algorithm>

QuadTree::QuadTree(Vector2<float> pos, Vector2<float> size, unsigned int level, unsigned int maxLevel, unsigned int maxObjects):MAX_LEVEL(maxLevel),
																															MAX_OBJECT_COUNT(maxObjects)
{
	_quadPosition = pos;
	_quadSize = size;
	_level = level;

	_node1 = 0;
	_node2 = 0;
	_node3 = 0;
	_node4 = 0;
	_split = false;

	_halfx = _quadSize.x/2;
	_halfy = _quadSize.y/2;

	_quadGameObjects.reserve(MAX_OBJECT_COUNT);

	_createdNodes = false;
}

QuadTree::~QuadTree()
{
	delete _node1;
	delete _node2;
	delete _node3;
	delete _node4;
}

void QuadTree::insert(CollidableObject *collidableObject)
{
	if(!_split)
	{
		_quadGameObjects.push_back( collidableObject );
		if(_quadGameObjects.size() >= MAX_OBJECT_COUNT && _level != MAX_LEVEL)
		{
			//if we havnt yet created any nodes for this quadtree then create new nodes
			//these arent deleted when the quadtree is cleared, allowing them to be used
			//without having to re-initialise the nodes
			if(!_createdNodes)
			{
				_node1 = new QuadTree( Vector2<float>( _quadPosition.x, _quadPosition.y ),  Vector2<float>( _halfx, _halfy), _level + 1, MAX_LEVEL, MAX_OBJECT_COUNT);
				_node2 = new QuadTree( Vector2<float>( _quadPosition.x + _halfx, _quadPosition.y ),  Vector2<float>( _halfx, _halfy), _level + 1, MAX_LEVEL, MAX_OBJECT_COUNT);
				_node3 = new QuadTree( Vector2<float>( _quadPosition.x, _quadPosition.y + _halfy ),  Vector2<float>( _halfx, _halfy), _level + 1, MAX_LEVEL, MAX_OBJECT_COUNT);
				_node4 = new QuadTree( Vector2<float>( _quadPosition.x + _halfx, _quadPosition.y + _halfy ), Vector2<float>( _halfx, _halfy), _level + 1, MAX_LEVEL, MAX_OBJECT_COUNT);
				_createdNodes = true;
			}

			//set the node to be split
			_split = true;

			//move all game objects that fit within a node exactly into a node
			//if a game object doesnt fit within the node exactly then keep
			//the object in this node
			std::vector<CollidableObject*> tempCollidableObjects(_quadGameObjects);
			//clear the original vector and re-insert each item
			_quadGameObjects.clear();
			unsigned int tempCollidableObjectsLength = tempCollidableObjects.size();
			for(unsigned int tempCollidableObjectsIndex = 0; tempCollidableObjectsIndex < tempCollidableObjectsLength; ++ tempCollidableObjectsIndex)
			{
				insert(tempCollidableObjects[tempCollidableObjectsIndex]);
			}
			//clear the temp vector
			tempCollidableObjects.clear();
		}
	}
	else
	{
		float collidableObjectWidth = collidableObject->getCollisionBoundsWidth();
		float collidableObjectHeight = collidableObject->getCollisionBoundsHeight();
		float collidableObjectLeft = collidableObject->getCollisionBoundsLeft();
		float collidableObjectTop = collidableObject->getCollisionBoundsTop();
		float collidableObjectRight = collidableObjectLeft + collidableObjectWidth;
		float collidableObjectBottom = collidableObjectTop + collidableObjectHeight;

		//quad1
		if(collidableObjectRight >= _quadPosition.x && collidableObjectLeft <= _quadPosition.x + _halfx && 
		   collidableObjectBottom >= _quadPosition.y && collidableObjectTop <= _quadPosition.y + _halfy)
		{
			_node1->insert(collidableObject);
		}

		// quad2
		if(collidableObjectRight >= _quadPosition.x + _halfx && collidableObjectLeft <= _quadPosition.x + _quadSize.x && 
		   collidableObjectBottom >= _quadPosition.y && collidableObjectTop <= _quadPosition.y + _halfy)
		{
			_node2->insert(collidableObject);
		}

		//quad3
		if(collidableObjectRight >= _quadPosition.x && collidableObjectLeft <= _quadPosition.x + _halfx && 
		   collidableObjectBottom >= _quadPosition.y + _halfy && collidableObjectTop <= _quadPosition.y + _quadSize.y)
		{
			_node3->insert(collidableObject);
		}

		//quad4
		if(collidableObjectRight >= _quadPosition.x + _halfx && collidableObjectLeft <= _quadPosition.x + _quadSize.x && 
		   collidableObjectBottom >= _quadPosition.y + _halfy && collidableObjectTop <= _quadPosition.y + _quadSize.y)
		{
			_node4->insert(collidableObject);
		}
	}
}

void QuadTree::retrieve(CollidableObject *collidableObject, std::vector<CollidableObject*>& objects)
{
	if(!_split)
	{
		if(std::find(_quadGameObjects.begin(), _quadGameObjects.end(), collidableObject) != _quadGameObjects.end())
		{
			objects.insert(objects.end(), _quadGameObjects.begin(), _quadGameObjects.end());
		}
	}
	else
	{
		_node1->retrieve(collidableObject, objects);
		_node2->retrieve(collidableObject, objects);
		_node3->retrieve(collidableObject, objects);
		_node4->retrieve(collidableObject, objects);
	}
}

void QuadTree::clear()
{
	if(_split)
	{
		_node1->clear();
		_node2->clear();
		_node3->clear();
		_node4->clear();
		_split = false;
	}
	_quadGameObjects.clear();
}