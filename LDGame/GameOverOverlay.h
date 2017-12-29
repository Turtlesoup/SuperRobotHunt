#ifndef GAME_OVER_OVERLAY_H
#define GAME_OVER_OVERLAY_H

#include "DisplayObject.h"
#include "GameScene.h"

class BorderedTextBox;

class GameOverOverlay : public DisplayObject
{
	public:
		GameOverOverlay();
		virtual ~GameOverOverlay();
		void update(float deltaTime);
		void showNewHighScore(unsigned int score);
	private:
		BorderedTextBox *_gameOverText;
		BorderedTextBox *_newHighScoreText;
		BorderedTextBox *_newHighScoreValueText;
};

#endif