#ifndef QUADTREE_H
#define QUADTREE_H

#include "Vector2.h"
#include <vector>

class CollidableObject;

class QuadTree
{
public:
	QuadTree(Vector2<float> pos, Vector2<float> size, unsigned int level, unsigned int maxLevel = 3, unsigned int maxObjects = 500);
	virtual ~QuadTree();
	void insert(CollidableObject *collidableObject);
	void retrieve(CollidableObject *collidableObject, std::vector<CollidableObject*>& objects);
	void clear();
private:
	QuadTree* _node1;
	QuadTree* _node2;
	QuadTree* _node3;
	QuadTree* _node4;
	std::vector<CollidableObject*> _quadGameObjects;
	int _level;
	const int MAX_LEVEL;
	const int MAX_OBJECT_COUNT;
	Vector2<float> _quadPosition;
	Vector2<float> _quadSize;
	bool _split;
	bool _createdNodes;
	int _halfx;
	int _halfy;
};

#endif