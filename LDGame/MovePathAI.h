#ifndef MOVE_PATH_AI_H
#define MOVE_PATH_AI_H

#include "BaseAI.h"

struct MovePathAIData : public BaseAIData
{
	public:
		MovePathAIData(unsigned int aiType, float movePathDirectionX, float movePathDirectionY) : BaseAIData(aiType),
																								  movePathDirectionX(movePathDirectionX),
																								  movePathDirectionY(movePathDirectionY){}
		virtual ~MovePathAIData(){}
		float movePathDirectionX;
		float movePathDirectionY;
};

class MovePathAI : public BaseAI
{
	public:
		MovePathAI(Enemy *parent, float movePathDirectionX, float movePathDirectionY);
		virtual ~MovePathAI();
		virtual void update(float deltaTime);
		virtual void onDetected();
		virtual void onUndetected();
		virtual void onHitBoundsLeft();
		virtual void onHitBoundsRight();
		virtual void onHitBoundsTop();
		virtual void onHitBoundsBottom();
	protected:
		float _movePathDirectionX;
		float _movePathDirectionY;
};

#endif