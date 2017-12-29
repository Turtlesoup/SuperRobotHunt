#ifndef GAME_STATE_WAVE_COMPLETE_H
#define GAME_STATE_WAVE_COMPLETE_H

#include "BaseState.h"
#include "KeyListener.h"

class GameScene;
class Player;

class GameStateWaveComplete : public BaseState, public KeyListener
{
	public:
		GameStateWaveComplete(GameStateManager *parent, GameScene *gameScene);
		virtual ~GameStateWaveComplete();
		void onStart(GAME_STATE previousState);
		void onUpdate(float deltaTime);
		void onQuit();
	protected:
		void onKeyPressed(EventData *eventData);
		void onKeyReleased(EventData *eventData);
	private:
		GameScene *_gameScene;
		Player *_player;
		bool _playerMovingUp;
		bool _playerMovingDown;
		bool _playerMovingLeft;
		bool _playerMovingRight;
		bool _playerShooting;
		float _currentDelayTime;
		float WAVE_COMPLETE_DELAY_TIME;
};

#endif