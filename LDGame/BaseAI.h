#ifndef BASE_AI_H
#define BASE_AI_H

enum AI_TYPES
{
	AI_TYPE_NONE,
	AI_TYPE_CHASE,
	AI_TYPE_CHASE_EXPLODE,
	AI_TYPE_MOVE_PATH
};

struct BaseAIData
{
	public:
		BaseAIData(unsigned int aiType) : AI_TYPE(aiType){}
		virtual ~BaseAIData(){}
		unsigned int AI_TYPE;
};

class Enemy;

class BaseAI
{
	public:
		BaseAI(Enemy *parent);
		virtual ~BaseAI();
		unsigned int aiTypeID();
		virtual void update(float deltaTime);
		virtual void onDetected();
		virtual void onUndetected();
		virtual bool hasDetectedPlayer();
		virtual void onHitBoundsLeft();
		virtual void onHitBoundsRight();
		virtual void onHitBoundsTop();
		virtual void onHitBoundsBottom();
	protected:
		bool _hasDetectedPlayer;
		unsigned int _aiTypeID;
		Enemy *_parent;
};

#endif