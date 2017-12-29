#include "CollisionManager.h"
#include "CollidableObject.h"
#include "QuadTree.h"
#include "Application.h"

#include <numeric>

CollisionManager *CollisionManager::_instance = nullptr;

CollisionManager *CollisionManager::Get()
{
	if(_instance == 0)
	{
		_instance = new CollisionManager();
	}

	return _instance;
}

CollisionManager::CollisionManager()
{
	_rootQuad = new QuadTree(Vector2<float>(0,0), Vector2<float>(Application::screenWidth(), Application::screenHeight()), 0);
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::addCollidableObject(CollidableObject* collidableObject)
{
	if(collidableObject->getCollidable())
	{
		//insert the collidable object into the quadtree
		_rootQuad->insert(collidableObject);

		//add the collidable object to the collidable objects vector
		//so that we can only check for collision on these objects
		_collidableObjects.push_back(collidableObject);

		//if the object is set to check for collisions then add
		//this object to the collision checking objects vector
		if(collidableObject->getCollisionChecking())
		{
			_collisionCheckingObjects.push_back(collidableObject);
		}
	}
}

void CollisionManager::removeCollidableObject(CollidableObject* collidableObject)
{
	std::vector<CollidableObject*>::iterator collidableObjectsIterator;

	//remove the object from the collidable objects list
	collidableObjectsIterator = std::find(_collidableObjects.begin(), _collidableObjects.end(), collidableObject);
	if(collidableObjectsIterator != _collidableObjects.end())
	{
		_collidableObjects.erase(collidableObjectsIterator);
	}

	//remove the object from the collison checking object
	collidableObjectsIterator = std::find(_collisionCheckingObjects.begin(), _collisionCheckingObjects.end(), collidableObject);
	if(collidableObjectsIterator != _collisionCheckingObjects.end())
	{
		_collisionCheckingObjects.erase(collidableObjectsIterator);
	}
}

void CollisionManager::checkCollisions()
{
	//check for collisions
	checkBoundCollisions();
	checkRayCollisions();

	//clear the quadtree
	_rootQuad->clear();

	//clear the collidable objects and collision checking objects vectors
	_collidableObjects.clear();
	_collisionCheckingObjects.clear();
	_rayCasts.clear();
}

void CollisionManager::checkBoundCollisions()
{
	CollidableObject* collidableObject;
	CollidableObject* candidateCollidableObject;
	COLLISION_LAYERS collisionLayer;
	std::vector<CollidableObject*> candidateCollidableObjects;
	std::vector<CollidableObject*>::iterator collidableObjectsIter, collidableObjectsIterEnd, candidateCollidableObjectsIter, candidateCollidableObjectsIterEnd;
	for(collidableObjectsIter = _collisionCheckingObjects.begin(), collidableObjectsIterEnd = _collisionCheckingObjects.end(); collidableObjectsIter != collidableObjectsIterEnd; ++ collidableObjectsIter)
	{
		collidableObject = (*collidableObjectsIter);

		//retrieve the collidable objects within the same node as the object we wish to check
		_rootQuad->retrieve(collidableObject, candidateCollidableObjects);

		//get the collision layer flag for the object
		collisionLayer = collidableObject->getCollisionCheckingLayer();

		//check for collision bounds intersection on each candidate in the candidates vector
		for(candidateCollidableObjectsIter = candidateCollidableObjects.begin(), candidateCollidableObjectsIterEnd = candidateCollidableObjects.end(); candidateCollidableObjectsIter != candidateCollidableObjectsIterEnd; ++ candidateCollidableObjectsIter)
		{
			candidateCollidableObject = (*candidateCollidableObjectsIter);
			
			//if the candidate object is on the same layer as the collision checking object, and is not
			//the collision checking object itself, and the boundaries intersect, then we have a collision
			if(collisionLayer & candidateCollidableObject->getCollisionLayer() &&
			   collidableObject != candidateCollidableObject &&
			   collidableObject->getCollisionBounds().intersects(candidateCollidableObject->getCollisionBounds()))
			{
				collidableObject->onCollision(candidateCollidableObject);
				candidateCollidableObject->onCollision(collidableObject);
			}
		}

		//clear the candidates list
		candidateCollidableObjects.clear();
	}
}

void CollisionManager::addRayCastCheck(CollidableObject* owner, Vector2<float> origin, Vector2<float> direction, COLLISION_LAYERS layerMask, float distance, unsigned int stopAfterCollisionsCount)
{
	RayCast rayCast;
	rayCast.owner = owner;
	rayCast.ray = new Ray(origin, direction, layerMask, distance);
	rayCast.stopAfterCollisionsCount = stopAfterCollisionsCount;

	_rayCasts.push_back(rayCast);
}

struct sortByProximityToRayOrigin
{
	inline bool operator() (RayCollidedObject &object1, RayCollidedObject &object2)
	{
		return (object1.rayIntersectionDistance < object2.rayIntersectionDistance);
	}
};

void CollisionManager::checkRayCollisions()
{
	std::vector<RayCast>::iterator raycastsIterator, raycastsBegin, raycastsEnd;
	raycastsBegin = _rayCasts.begin();
	raycastsEnd = _rayCasts.end();

	RayCast raycast;
	Ray *ray;
	CollidableObject* collidableObject;
	COLLISION_LAYERS collisionLayer;

	std::vector<CollidableObject*>::iterator candidateCollidableObjectsIter, candidateCollidableObjectsBegin, candidateCollidableObjectsEnd;
	candidateCollidableObjectsBegin = _collidableObjects.begin();
	candidateCollidableObjectsEnd = _collidableObjects.end();

	CollidableObject* candidateCollidableObject;
	float rayIntersectionDistance;

	std::vector<RayCollidedObject> rayCollidedObjects;
	std::vector<RayCollidedObject>::iterator rayCollidedObjectsIter, rayCollidedObjectsBegin, rayCollidedObjectsEnd;
	unsigned int numberOfRayCollisionsRemaining;

	for(raycastsIterator = raycastsBegin; raycastsIterator != raycastsEnd; ++ raycastsIterator)
	{
		raycast = (*raycastsIterator);
		ray = raycast.ray;
		collidableObject = raycast.owner;
		collisionLayer = ray->layerMask();

		//check for collision bounds intersection on each candidate in the candidates vector
		for(candidateCollidableObjectsIter = candidateCollidableObjectsBegin; candidateCollidableObjectsIter != candidateCollidableObjectsEnd; ++ candidateCollidableObjectsIter)
		{
			candidateCollidableObject = (*candidateCollidableObjectsIter);
			
			//if the ray is on the same layer as the collision checking object, and is not the ray owner object itself...
			if(collisionLayer & candidateCollidableObject->getCollisionLayer() &&
			   collidableObject != candidateCollidableObject)
			{
				//...and the ray intersection distance is valid (not MAX FLOAT value), then we have a collision.
				rayIntersectionDistance = ray->intersect(candidateCollidableObject->getCollisionBounds());
				if(rayIntersectionDistance != FLT_MAX)
				{
					//add the object to the ray colliding objects for this ray along with the distance of the ray
					//at this collision. We can then use this distance in order to determine which objects where
					//hit in what order by the ray.
					RayCollidedObject rayCollidedObject;
					rayCollidedObject.object = candidateCollidableObject;
					rayCollidedObject.rayIntersectionDistance = rayIntersectionDistance;

					rayCollidedObjects.push_back(rayCollidedObject);
				}
			}
		}

		if(rayCollidedObjects.size() > 0)
		{
			//get the collided objects iterator begining and end
			rayCollidedObjectsBegin = rayCollidedObjects.begin();
			rayCollidedObjectsEnd = rayCollidedObjects.end();

			//sort the ray collided objects by proximity to the rays origin
			std::sort(rayCollidedObjectsBegin, rayCollidedObjectsEnd, sortByProximityToRayOrigin());

			//now for all objects which intersected the ray, collide with the objects
			//until the ray's number of collisions until it stops have been reached.
			numberOfRayCollisionsRemaining = raycast.stopAfterCollisionsCount;
			for(rayCollidedObjectsIter = rayCollidedObjectsBegin; rayCollidedObjectsIter != rayCollidedObjectsEnd; ++ rayCollidedObjectsIter)
			{
				candidateCollidableObject = (*rayCollidedObjectsIter).object;
				float rayIntersectionDistance = (*rayCollidedObjectsIter).rayIntersectionDistance;

				collidableObject->onRayCollision(candidateCollidableObject, ray, rayIntersectionDistance);
				candidateCollidableObject->onRayCollision(collidableObject, ray, rayIntersectionDistance);

				-- numberOfRayCollisionsRemaining;
				if(numberOfRayCollisionsRemaining == 0)
				{
					break;
				}
			}
		}
		else
		{
			//the ray hit nothing so call the on ray collison will a null pointer for the collided object argument
			collidableObject->onRayCollision(nullptr, ray, FLT_MAX);
		}

		//clear the ray colliding objects vector
		rayCollidedObjects.clear();

		//delete the ray as it is no longer needed
		delete ray;
	}

	_rayCasts.clear();
}