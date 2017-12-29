#include "GameStatePaused.h"
#include "GameScene.h"
#include "MathHelper.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "SceneManager.h"
#include "Application.h"
#include "MenuPopup.h"
#include "OptionsPopup.h"
#include "AreYouSurePopup.h"
#include "Vector2.h"
#include "AudioManager.h"
#include "Resources.h"

GameStatePaused::GameStatePaused(GameStateManager *parent, GameScene *gameScene) : BaseState(parent),
																				   KeyListener(false),
																				   _gameScene(gameScene)
{
	//create the menu and are you sure popup
	float screenMaxX = _gameScene->getScreenBoundsMaxX();
	float screenMaxY = _gameScene->getScreenBoundsMaxY();

	_menuPopup = new MenuPopup(Vector2<float>(screenMaxX/2, screenMaxY/2), Vector2<float>(screenMaxX/2, screenMaxY*2), std::bind<void>(&GameStatePaused::resumeGame, this), std::bind<void>(&GameStatePaused::showOptions, this), std::bind<void>(&GameStatePaused::showAreYouSurePopup, this));
	_menuPopup->disableListeners();

	_optionsPopup = new OptionsPopup(Vector2<float>(screenMaxX/2, screenMaxY/2), Vector2<float>(screenMaxX/2, screenMaxY*2), std::bind<void>(&GameStatePaused::onOptionsPopupClosed, this));
	_optionsPopup->disableListeners();

	_areYouSurePopup = new AreYouSurePopup(Vector2<float>(screenMaxX/2, screenMaxY/2), Vector2<float>(screenMaxX/2, screenMaxY*2), std::bind<void>(&GameStatePaused::exitToTitleScene, this), std::bind<void>(&GameStatePaused::resumeGame, this));
	_areYouSurePopup->disableListeners();

	//add the popup to the uiLayer
	_gameScene->uiLayer()->addChild(_menuPopup);
	_gameScene->uiLayer()->addChild(_optionsPopup);
	_gameScene->uiLayer()->addChild(_areYouSurePopup);
}

GameStatePaused::~GameStatePaused()
{
}

void GameStatePaused::onStart(GAME_STATE previousState)
{
	_previousState = previousState;

	//pause the game layers
	_gameScene->tileMapLayer()->pause(true);
	_gameScene->gameLayer()->pause(true);
	_gameScene->underLightLayer()->pause(true);
	_gameScene->overObjectsLayer()->pause(true);

	//show the menu popup
	_menuPopup->enableListeners();
	_menuPopup->showPopup();

	//enable listeners
	enableListeners();

	//play the paused sfx
	AudioManager::Get()->playSound(AUDIO_GAME_PAUSED);
}


void GameStatePaused::onKeyPressed(EventData *eventData)
{
	KeyPressedEventData *keyPressedEventData = dynamic_cast<KeyPressedEventData*>(eventData);
	if(keyPressedEventData != nullptr)
	{
		switch(keyPressedEventData->getKeycode())
		{
		}
	}
}

void GameStatePaused::onKeyReleased(EventData *eventData)
{
	KeyReleasedEventData *keyReleasedEventData = dynamic_cast<KeyReleasedEventData*>(eventData);
	if(keyReleasedEventData != nullptr)
	{
		switch(keyReleasedEventData->getKeycode())
		{
		}
	}
}

void GameStatePaused::onUpdate(float deltaTime)
{
}

void GameStatePaused::onQuit()
{
	_menuPopup->disableListeners();
	_areYouSurePopup->disableListeners();

	//disable listeners
	disableListeners();

	//play the paused sfx
	AudioManager::Get()->playSound(AUDIO_GAME_PAUSED);
}

void GameStatePaused::showAreYouSurePopup()
{
	//hide menu popup
	_menuPopup->disableListeners();
	_menuPopup->hidePopup();

	//show are you sure popup
	_areYouSurePopup->enableListeners();
	_areYouSurePopup->showPopup();
}

void GameStatePaused::resumeGame()
{
	if(_menuPopup->isShowing())
	{
		_menuPopup->hidePopup();
	}

	if(_areYouSurePopup->isShowing())
	{
		_areYouSurePopup->hidePopup();
	}
	
	_parent->changeState(_previousState);
}

void GameStatePaused::showOptions()
{
	_menuPopup->disableListeners();
	_menuPopup->hidePopup();

	_optionsPopup->enableListeners();
	_optionsPopup->showPopup();
}

void GameStatePaused::onOptionsPopupClosed()
{
	_menuPopup->enableListeners();
	_menuPopup->showPopup();
}

void GameStatePaused::exitToTitleScene()
{
	SceneManager::Get()->showScene(Application::TITLE_SCENE);
}