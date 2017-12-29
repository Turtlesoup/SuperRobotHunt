#ifndef GAME_STATE_PAUSED_H
#define GAME_STATE_PAUSED_H

#include "BaseState.h"
#include "KeyListener.h"

class GameScene;
class MenuPopup;
class OptionsPopup;
class AreYouSurePopup;

class GameStatePaused : public BaseState, public KeyListener
{
	public:
		GameStatePaused(GameStateManager *parent, GameScene *gameScene);
		virtual ~GameStatePaused();
		void onStart(GAME_STATE previousState);
		void onUpdate(float deltaTime);
		void onQuit();
	protected:
		void onKeyPressed(EventData *eventData);
		void onKeyReleased(EventData *eventData);
	private:
		void showAreYouSurePopup();
		void resumeGame();
		void showOptions();
		void onOptionsPopupClosed();
		void exitToTitleScene();
		GameScene *_gameScene;
		MenuPopup *_menuPopup;
		OptionsPopup *_optionsPopup;
		AreYouSurePopup *_areYouSurePopup;
		GAME_STATE _previousState;
};

#endif