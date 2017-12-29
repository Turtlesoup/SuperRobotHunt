#include "Application.h"
#include "EventData.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "SpriteDisplayObject.h"
#include "AnimatedDisplayObject.h"
#include "TextDisplayObject.h"
#include "EventManager.h"
#include "GameSceneData.h"
#include "TitlePanel.h"
#include "OptionsPopup.h"
#include "Resources.h"
#include "AudioManager.h"

TitleScene::TitleScene(SceneData *sceneData) : Scene(sceneData)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::onStart()
{
	Scene::onStart();

	//initialise font
	_font.loadFromFile("../assets/Arial.ttf");

	//create title panel
	float zoom = Application::zoom();
	float screenWidth = Application::screenWidth() / zoom;
	float screenHeight = Application::screenHeight() / zoom;

	_background = new SpriteDisplayObject(SPRITE_MENU_BACKGROUND, TEXTURE_ATLAS_SPRITES, Vector2<float>(screenWidth * 0.5, screenHeight * 0.5));
	_background->setWidth(screenWidth);
	_background->setHeight(screenHeight);
	addChild(_background);

	_titlePanel = new TitlePanel(Vector2<float>(screenWidth * 0.5, screenHeight * 0.5), Vector2<float>(screenWidth * 0.5, screenHeight * 2), std::bind<void>(&TitleScene::startGame, this), std::bind<void>(&TitleScene::showOptions, this));
	_titlePanel->showPopup();
	addChild(_titlePanel);

	_optionsPopup = new OptionsPopup(Vector2<float>(screenWidth * 0.5, screenHeight * 0.5), Vector2<float>(screenWidth * 0.5, screenHeight * 2), std::bind<void>(&TitleScene::onOptionsPopupClosed, this));
	_optionsPopup->disableListeners();
	addChild(_optionsPopup);

	//start the menu music
	AudioManager::Get()->playMusic(MUSIC_MENU);
}

void TitleScene::onUpdate(float deltaTime)
{
	Scene::onUpdate(deltaTime);

	_titlePanel->update(deltaTime);
}

void TitleScene::onDispose()
{
	Scene::onDispose();

	AudioManager::Get()->stopMusic(MUSIC_MENU);
}

void TitleScene::onKeyPressed(sf::Keyboard::Key key)
{
}

void TitleScene::startGame()
{
	SceneManager::Get()->showScene(Application::GAME_SCENE, new GameSceneData());
}

void TitleScene::showOptions()
{
	_titlePanel->disableListeners();
	_optionsPopup->enableListeners();
	_optionsPopup->showPopup();
}

void TitleScene::onOptionsPopupClosed()
{
	_titlePanel->enableListeners();
}