#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "BaseState.h"
#include <map>

class GameScene;

class GameStateManager
{
	public:
		GameStateManager();
		virtual ~GameStateManager();
		void init(GameScene *gameScene);
		void changeState(GAME_STATE state);
		void update(float deltaTime);
		GAME_STATE currentState();
	private:
		GAME_STATE _currentState;
		std::map<GAME_STATE, BaseState*> _states;
};

#endif