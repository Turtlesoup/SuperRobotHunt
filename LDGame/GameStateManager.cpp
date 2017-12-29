#include "GameStateManager.h"
#include "GameScene.h"
#include "GameStateNormal.h"
#include "GameStatePaused.h"
#include "GameStateWaveComplete.h"
#include "GameStateGameOver.h"

GameStateManager::GameStateManager() : _currentState(STATE_NORMAL)
{
}

GameStateManager::~GameStateManager()
{
	//delete the states
	std::map<GAME_STATE, BaseState*>::iterator statesIterator, statesEnd;
	for(statesIterator = _states.begin(), statesEnd = _states.end(); statesIterator != statesEnd; ++ statesIterator)
	{
		delete (*statesIterator).second;
	}
	_states.clear();
}

void GameStateManager::init(GameScene *gameScene)
{
	_states[STATE_NORMAL] = new GameStateNormal(this, gameScene);
	_states[STATE_PAUSED] = new GameStatePaused(this, gameScene);
	_states[STATE_WAVE_COMPLETE] = new GameStateWaveComplete(this, gameScene);
	_states[STATE_GAME_OVER] = new GameStateGameOver(this, gameScene);

	_currentState = STATE_NORMAL;
	_states[_currentState]->onStart(STATE_NONE);
}

void GameStateManager::changeState(GAME_STATE state)
{
	if(_currentState != state)
	{
		//quit the current state before the switch
		_states[_currentState]->onQuit();

		//start the new state
		GAME_STATE previousState = _currentState;
		_currentState = state;
		_states[_currentState]->onStart(previousState);
	}
}

void GameStateManager::update(float deltaTime)
{
	_states[_currentState]->onUpdate(deltaTime);
}

GAME_STATE GameStateManager::currentState()
{
	return _currentState;
}