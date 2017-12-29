#include "GameStateGameOver.h"
#include "GameScene.h"
#include "MathHelper.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "SceneManager.h"
#include "Application.h"
#include "Vector2.h"
#include "PlayerData.h"
#include "PlayerDataConsts.h"
#include "GameOverOverlay.h"
#include "GameOverPanel.h"
#include "AudioManager.h"
#include "Resources.h"

GameStateGameOver::GameStateGameOver(GameStateManager *parent, GameScene *gameScene) : BaseState(parent),
																					   KeyListener(false),
																					   _gameScene(gameScene),
																					   GAME_OVER_WAIT_TIME(1000),
																					   _currentWaitTime(GAME_OVER_WAIT_TIME)
{
	float screenMaxX = _gameScene->getScreenBoundsMaxX();
	float screenMaxY = _gameScene->getScreenBoundsMaxY();

	//create game over overlay
	_gameOverOverlay = new GameOverOverlay();
	_gameScene->uiLayer()->addChild(_gameOverOverlay);

	_gameOverOverlay->setVisible(false);

	//create game over panel
	_gameOverPanel = new GameOverPanel(Vector2<float>(screenMaxX/2, screenMaxY * 0.9), Vector2<float>(screenMaxX/2, screenMaxY*2), std::bind<void>(&GameStateGameOver::retryGame, this), std::bind<void>(&GameStateGameOver::exitToTitleScene, this));
	_gameOverPanel->disableListeners();

	_gameScene->uiLayer()->addChild(_gameOverPanel);
}

GameStateGameOver::~GameStateGameOver()
{
}

void GameStateGameOver::onStart(GAME_STATE previousState)
{
	//enable listeners
	enableListeners();

	//if the player gained a new highscore then save the new score
	PlayerData::Get()->loadExternal();

	unsigned int currentHighscore;
	if(PlayerData::Get()->hasElement(HIGHSCORE))
	{
		currentHighscore = PlayerData::Get()->getElement(HIGHSCORE);
	}
	else
	{
		currentHighscore = 0;
	}

	unsigned int currentScore = _gameScene->getCurrentScore();
	if(currentScore >= currentHighscore)
	{
		//save the new highscore
		PlayerData::Get()->setElement(HIGHSCORE, currentScore);
		PlayerData::Get()->saveExternal();

		//show the new highscore
		_gameOverOverlay->showNewHighScore(currentScore);
	}

	//set the wait time
	_currentWaitTime = GAME_OVER_WAIT_TIME;

	//play the paused sfx
	AudioManager::Get()->playSound(AUDIO_GAME_OVER);
}


void GameStateGameOver::onKeyPressed(EventData *eventData)
{
	KeyPressedEventData *keyPressedEventData = dynamic_cast<KeyPressedEventData*>(eventData);
	if(keyPressedEventData != nullptr)
	{
		switch(keyPressedEventData->getKeycode())
		{
		}
	}
}

void GameStateGameOver::onKeyReleased(EventData *eventData)
{
	KeyReleasedEventData *keyReleasedEventData = dynamic_cast<KeyReleasedEventData*>(eventData);
	if(keyReleasedEventData != nullptr)
	{
		switch(keyReleasedEventData->getKeycode())
		{
		}
	}
}

void GameStateGameOver::onUpdate(float deltaTime)
{
	_gameOverOverlay->update(deltaTime);

	if(_currentWaitTime > 0)
	{
		_currentWaitTime -= deltaTime;
		if(_currentWaitTime <= 0)
		{
			_currentWaitTime = 0;

			//show the retry/quit buttons
			showGameOverPanel();
		}
	}
}

void GameStateGameOver::onQuit()
{
	//disable listeners
	disableListeners();

	//hide game over overlay
	_gameOverOverlay->setVisible(false);
}

void GameStateGameOver::showGameOverPanel()
{
	//pause the game layers
	_gameScene->tileMapLayer()->pause(true);
	_gameScene->gameLayer()->pause(true);
	_gameScene->underLightLayer()->pause(true);
	_gameScene->overObjectsLayer()->pause(true);

	//show the game over panel
	_gameOverOverlay->setVisible(true);
	_gameOverPanel->enableListeners();
	_gameOverPanel->showPopup();
}

void GameStateGameOver::retryGame()
{
	SceneManager::Get()->showScene(Application::GAME_SCENE);
}

void GameStateGameOver::exitToTitleScene()
{
	SceneManager::Get()->showScene(Application::TITLE_SCENE);
}