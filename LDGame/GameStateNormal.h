#ifndef GAME_STATE_NORMAL_H
#define GAME_STATE_NORMAL_H

#include "BaseState.h"
#include "KeyListener.h"

class GameScene;
class Player;

class GameStateNormal : public BaseState, public KeyListener
{
	public:
		GameStateNormal(GameStateManager *parent, GameScene *gameScene);
		virtual ~GameStateNormal();
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
};

#endif