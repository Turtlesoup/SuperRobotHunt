#include "GameOverOverlay.h"
#include "BorderedTextBox.h"
#include "Application.h"

GameOverOverlay::GameOverOverlay() : DisplayObject(Vector2<float>(0, 0))
{
	float scaleFactor = Application::zoom();
	float screenWidth = (Application::screenWidth() / scaleFactor);
	float screenHeight = (Application::screenHeight() / scaleFactor) - (32*scaleFactor);

	_gameOverText = new BorderedTextBox("Game Over", Vector2<float>(screenWidth * 0.5, screenHeight * 0.34), sf::Color(255, 100, 100), sf::Color(255, 255, 255), 64);
	addChild(_gameOverText);

	_newHighScoreText = new BorderedTextBox("New HighScore!", Vector2<float>(screenWidth * 0.5, screenHeight * 0.67), sf::Color(255, 100, 100), sf::Color(255, 255, 255), 55);
	addChild(_newHighScoreText);
	_newHighScoreText->setVisible(false);

	_newHighScoreValueText = new BorderedTextBox("", Vector2<float>(screenWidth * 0.5, screenHeight * 0.80), sf::Color(255, 100, 100), sf::Color(255, 255, 255), 64);
	addChild(_newHighScoreValueText);
	_newHighScoreValueText->setVisible(false);
}

GameOverOverlay::~GameOverOverlay()
{
}

void GameOverOverlay::update(float deltaTime)
{
}

void GameOverOverlay::showNewHighScore(unsigned int score)
{
	_newHighScoreText->setVisible(true);
	_newHighScoreValueText->setVisible(true);

	_newHighScoreValueText->setText(std::to_string((long double)score));
}