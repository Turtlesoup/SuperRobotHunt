#ifndef GAME_STATE_GAME_OVER_H
#define GAME_STATE_GAME_OVER_H

#include "BaseState.h"
#include "KeyListener.h"

class GameScene;
class GameOverOverlay;
class GameOverPanel;

class GameStateGameOver : public BaseState, public KeyListener
{
	public:
		GameStateGameOver(GameStateManager *parent, GameScene *gameScene);
		virtual ~GameStateGameOver();
		void onStart(GAME_STATE previousState);
		void onUpdate(float deltaTime);
		void onQuit();
	protected:
		void onKeyPressed(EventData *eventData);
		void onKeyReleased(EventData *eventData);
	private:
		void showGameOverPanel();
		void retryGame();
		void exitToTitleScene();
		GameScene *_gameScene;
		GameOverOverlay *_gameOverOverlay;
		GameOverPanel *_gameOverPanel;
		const float GAME_OVER_WAIT_TIME;
		float _currentWaitTime;
};

#endif