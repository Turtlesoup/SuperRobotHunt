#include "GameStateNormal.h"
#include "GameScene.h"
#include "MathHelper.h"
#include "Player.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "SceneManager.h"
#include "Application.h"

const float SHAKE_SPACING = 3;

GameStateNormal::GameStateNormal(GameStateManager *parent, GameScene *gameScene) : BaseState(parent),
																				   KeyListener(false),
																				   _gameScene(gameScene)
{
}

GameStateNormal::~GameStateNormal()
{
}

void GameStateNormal::onStart(GAME_STATE previousState)
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
}


void GameStateNormal::onKeyPressed(EventData *eventData)
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

void GameStateNormal::onKeyReleased(EventData *eventData)
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

void GameStateNormal::onUpdate(float deltaTime)
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
}

void GameStateNormal::onQuit()
{
	//disable listeners
	disableListeners();
}