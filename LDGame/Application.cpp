#include "TextureManager.h"
#include "TextureAtlas.h"
#include "SceneManager.h"
#include "SceneData.h"
#include "AudioManager.h"
#include "Application.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "StringHelper.h"
#include "Resources.h"
#include "BulletTypeDataManager.h"
#include "EnemyTypeDataManager.h"
#include "WaveManager.h"
#include "PlayerData.h"

const std::string GAME_VERSION = "1.0.0";

Application::Application() : Game(1024, 768, 2.0f, false, false, "Super Robot Hunt")
{
	//seed rand
	srand(time(NULL));

	//load audio
	_audioManager->loadSound(AUDIO_BUTTON_RELEASED);
	_audioManager->loadSound(AUDIO_COLLECT_HEALTH);
	_audioManager->loadSound(AUDIO_COLLECT_SMALL_GEM);
	_audioManager->loadSound(AUDIO_COLLECT_GEM);
	_audioManager->loadSound(AUDIO_COLLECT_WEAPON);
	_audioManager->loadSound(AUDIO_PLAYER_HIT);
	_audioManager->loadSound(AUDIO_GAME_START);
	_audioManager->loadSound(AUDIO_GAME_OVER);
	_audioManager->loadSound(AUDIO_GAME_PAUSED);

	std::vector<std::string> resourceURLs;

	//initialise the bullet type data manager
	BulletTypeDataManager::Get()->init(resourceURLs);

	//initialise the enemy type data manager
	EnemyTypeDataManager::Get()->init(resourceURLs);

	//initialise the wave manager
	WaveManager::Get()->init();

	//create and add texture atlas
	TextureAtlas textureAtlas;
	
	resourceURLs.push_back(SPRITE_PLAYER);
	resourceURLs.push_back(SPRITE_CIRCLE_FLASH);
	resourceURLs.push_back(SPRITE_GAUSSIAN);
	resourceURLs.push_back(SPRITE_TILES);
	resourceURLs.push_back(SPRITE_EXPLOSION);
	resourceURLs.push_back(SPRITE_COLLECTABLE_1);
	resourceURLs.push_back(SPRITE_COLLECTABLE_2);
	resourceURLs.push_back(SPRITE_COLLECTABLE_3);
	resourceURLs.push_back(SPRITE_COLLECTABLE_4);
	resourceURLs.push_back(FONT_PNG);
	resourceURLs.push_back(SPRITE_BACKGROUND_PANEL);
	resourceURLs.push_back(SPRITE_BUTTON);
	resourceURLs.push_back(SPRITE_HEALTH_BAR_SEGMENT);
	resourceURLs.push_back(SPRITE_HEALTH_BAR_SEGMENT_EMPTY);
	resourceURLs.push_back(SPRITE_MENU_BACKGROUND);
	textureAtlas.create(1024, 2048, resourceURLs);
	//textureAtlas.saveToFile("textureAtlas.png");

	_textureManager->addTextureAtlas(TEXTURE_ATLAS_SPRITES, textureAtlas);

	//load gui datas and bitmap font
	GuiManager::Get()->loadGuiLayoutData(GUI_JSON_OPTIONS_POPUP);
	GuiManager::Get()->loadGuiLayoutData(GUI_JSON_MENU_POPUP);
	GuiManager::Get()->loadGuiLayoutData(GUI_JSON_ARE_YOU_SURE_POPUP);
	GuiManager::Get()->loadGuiLayoutData(GUI_JSON_GAME_OVER_PANEL);
	GuiManager::Get()->loadGuiLayoutData(GUI_JSON_TITLE_PANEL);
	GuiManager::Get()->addBitmapFont(FONT_FNT, FONT_PNG, TEXTURE_ATLAS_SPRITES);

	//load the external player data
	PlayerData::Get()->loadExternal();
}

Application::~Application()
{
}

Scene* Application::createScene(unsigned int sceneID, SceneData *sceneData)
{
	switch(sceneID)
	{
		case TITLE_SCENE:
			return new TitleScene(sceneData);
			break;

		case GAME_SCENE:
			return new GameScene(sceneData);
			break;
	}

	return 0;
}