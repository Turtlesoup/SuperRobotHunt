#include "GameStateWaveComplete.h"
#include "GameScene.h"
#include "MathHelper.h"
#include "Player.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "SceneManager.h"
#include "Application.h"
#include "Vector2.h"

const float SHAKE_SPACING = 3;

GameStateWaveComplete::GameStateWaveComplete(GameStateManager *parent, GameScene *gameScene) : BaseState(parent),
																							   KeyListener(false),
																							   _gameScene(gameScene),
																							   _currentDelayTime(0),
																							   WAVE_COMPLETE_DELAY_TIME(3000)
{
}

GameStateWaveComplete::~GameStateWaveComplete()
{
}

void GameStateWaveComplete::onStart(GAME_STATE previousState)
{
	_player = _gameScene->getPlayer();

	_playerMovingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	_playerMovingDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	_playerMovingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	_playerMovingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	_playerShooting = sf::Keyboard::isKeyPressed(sf::Keyboard::X);

	//unpause game layers
	_gameScene->tileMapLayer()->pause(false);
	_gameScene->gameLayer()->pause(false);
	_gameScene->underLightLayer()->pause(false);
	_gameScene->overObjectsLayer()->pause(false);

	//enable listeners
	enableListeners();

	if(previousState == STATE_NORMAL)
	{
		//setup the delay time
		_currentDelayTime = 0;

		//spawn wave complete
		_gameScene->spawnWaveCompleteIndicator();
	}
}


void GameStateWaveComplete::onKeyPressed(EventData *eventData)
{
	KeyPressedEventData *keyPressedEventData = dynamic_cast<KeyPressedEventData*>(eventData);
	if(keyPressedEventData != nullptr)
	{
		switch(keyPressedEventData->getKeycode())
		{
			case sf::Keyboard::Up:
				_playerMovingUp = true;
				break;
			case sf::Keyboard::Down:
				_playerMovingDown = true;
				break;
			case sf::Keyboard::Left:
				_playerMovingLeft = true;
				break;
			case sf::Keyboard::Right:
				_playerMovingRight = true;
				break;
			case sf::Keyboard::X:
				_playerShooting = true;
				break;
		}
	}
}

void GameStateWaveComplete::onKeyReleased(EventData *eventData)
{
	KeyReleasedEventData *keyReleasedEventData = dynamic_cast<KeyReleasedEventData*>(eventData);
	if(keyReleasedEventData != nullptr)
	{
		switch(keyReleasedEventData->getKeycode())
		{
			case sf::Keyboard::Up:
				_playerMovingUp = false;
				break;
			case sf::Keyboard::Down:
				_playerMovingDown = false;
				break;
			case sf::Keyboard::Left:
				_playerMovingLeft = false;
				break;
			case sf::Keyboard::Right:
				_playerMovingRight = false;
				break;
			case sf::Keyboard::X:
				_playerShooting = false;
				break;
			case sf::Keyboard::P:
			case sf::Keyboard::Escape:
				_parent->changeState(STATE_PAUSED);
				break;
		}
	}
}

void GameStateWaveComplete::onUpdate(float deltaTime)
{
	if(_playerMovingUp)
	{
		_player->moveUp(deltaTime);
	}
	else if(_playerMovingDown)
	{
		_player->moveDown(deltaTime);
	}

	if(_playerMovingLeft)
	{
		_player->moveLeft(deltaTime);
	}
	else if(_playerMovingRight)
	{
		_player->moveRight(deltaTime);
	}

	if(_playerShooting)
	{
		_player->shoot(deltaTime);
	}

	_currentDelayTime += deltaTime;
	if(_currentDelayTime > WAVE_COMPLETE_DELAY_TIME)
	{
		//spawn the next wave
		_gameScene->spawnNextWave();

		//change the state back to the normal game state
		_parent->changeState(STATE_NORMAL);
	}
}

void GameStateWaveComplete::onQuit()
{
	//disable listeners
	disableListeners();
}