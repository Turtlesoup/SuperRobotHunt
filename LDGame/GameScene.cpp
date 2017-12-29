#include "Application.h"
#include "EventManager.h"
#include "GameScene.h"
#include "GameObject.h"
#include "SceneLayer.h"
#include "DisplayObject.h"
#include "AudioManager.h"
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include "Light.h"
#include "FlickeringLight.h"
#include "CollectableWeapon.h"
#include "CollectableGem.h"
#include "CollectableSmallGem.h"
#include "CollectableHealth.h"
#include "SpriteBatch.h"
#include "MathHelper.h"
#include "SceneManager.h"
#include "TextDisplayObject.h"
#include "BaseGuiWidget.h"
#include "BaseSpriteGuiWidget.h"
#include "ButtonGuiWidget.h"
#include "EventData.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "TextIndicator.h"
#include "Resources.h"
#include "HealthBar.h"
#include "ScoreText.h"
#include "WaveText.h"
#include "BulletTypeDataManager.h"
#include "EnemyTypeDataManager.h"
#include "WaveManager.h"
#include "PlayerData.h"
#include "PlayerDataConsts.h"

#include <assert.h>

struct sortByYPosition
{
	inline bool operator() (GameObject* object1, GameObject* object2)
	{
		TransformableObject* object1Positionable = dynamic_cast<TransformableObject*>(object1);
		TransformableObject* object2Positionable = dynamic_cast<TransformableObject*>(object2);
		if(object1Positionable != nullptr && object2Positionable != nullptr)
		{
			return (object1Positionable->getY() < object2Positionable->getY());
		}
		else if(object1Positionable != nullptr)
		{
			return false;
		}
		else if(object2Positionable != nullptr)
		{
			return true;
		}
		return true;
	}
};

const std::string CRITICAL = "CRITICAL";
const std::string PLUS_SYMBOL = "+";
const float SHAKE_SPACING = 3;

GameScene::GameScene(SceneData *sceneData) : Scene(sceneData),
											 MIN_INDICATOR_TEXT_SIZE(12),
											 MAX_INDICATOR_TEXT_SIZE(64),
											 MIN_INDICATOR_VALUE_SIZE(0),
											 MAX_INDICATOR_VALUE_SIZE(50),
											 INITIAL_WAIT_TIME(3000),
											 _currentScore(0),
											 _currentWaveNumber(0),
											 _totalNumberOfEnemiesInWave(0),
											 _numberOfEnemiesKilledInWave(0),
											 _screenShakingTime(0),
											 _initialWaitTime(INITIAL_WAIT_TIME)
{
	if(sceneData != nullptr)
	{
		delete sceneData;
	}
}

GameScene::~GameScene()
{
}

void GameScene::onStart()
{
	Scene::onStart();

	//create and add display layers
	createLayers();

	//create the hud elements
	createHUD();

	//create and add the world elements
	createWorld();

	//setup the initial game state
	startGame();
}

void GameScene::onUpdate(float deltaTime)
{
	if(_initialWaitTime > 0)
	{
		_initialWaitTime -= deltaTime;
		if(_initialWaitTime <= 0)
		{
			_initialWaitTime = 0;

			//spawn the first wave
			spawnNextWave();
		}
	}

	_gameStateManager.update(deltaTime);

	std::vector<GameObject*>& gameObjects = _gameLayer->getGameObjects();
	std::sort(gameObjects.begin(), gameObjects.end(), sortByYPosition());

	Scene::onUpdate(deltaTime);

	if(_screenShakingTime > 0)
	{
		float xShake = MathHelper::randomFloatInRange(-SHAKE_SPACING, SHAKE_SPACING);
		float yShake = MathHelper::randomFloatInRange(-SHAKE_SPACING, SHAKE_SPACING);

		_gameLayer->setXOffset(xShake);
		_gameLayer->setYOffset(yShake);
		_overObjectsLayer->setXOffset(xShake);
		_overObjectsLayer->setYOffset(yShake);
		_underLightLayer->setXOffset(xShake);
		_underLightLayer->setYOffset(yShake);
		_tileMapLayer->setXOffset(xShake);
		_tileMapLayer->setYOffset(yShake);

		_screenShakingTime -= deltaTime;
		if(_screenShakingTime <= 0)
		{
			_gameLayer->setXOffset(0);
			_gameLayer->setYOffset(0);
			_overObjectsLayer->setXOffset(0);
			_overObjectsLayer->setYOffset(0);
			_underLightLayer->setXOffset(0);
			_underLightLayer->setYOffset(0);
			_tileMapLayer->setXOffset(0);
			_tileMapLayer->setYOffset(0);
		}
	}
}

void GameScene::onDispose()
{
	Scene::onDispose();

	AudioManager::Get()->stopMusic(MUSIC_GAME);
}

void GameScene::createLayers()
{
	//create layers
	_overObjectsLayer = new SceneLayer(sf::BlendAlpha);
	_gameLayer = new SceneLayer(sf::BlendAlpha);
	_underLightLayer = new SceneLayer(sf::BlendAdd, true);
	_tileMapLayer = new SceneLayer(sf::BlendAlpha);
	_uiLayer = new SceneLayer(sf::BlendAlpha);

	//set under light layer to multiply when rendering the render texture so that the lights illuminate the map
	_underLightLayer->setRenderTextureBlendMode(sf::BlendMultiply);
	_underLightLayer->setRenderTextureClearColour(sf::Color(100, 100, 100));

	//add the display layers
	addChild(_tileMapLayer);
	addChild(_underLightLayer);
	addChild(_gameLayer);
	addChild(_overObjectsLayer);
	addChild(_uiLayer);
}

void GameScene::createHUD()
{
	_healthBar = new HealthBar(Vector2<float>(20, 16));
	_uiLayer->addChild(_healthBar);

	_scoreText = new ScoreText(Vector2<float>(460,0), sf::Color(128, 0, 255, 255), sf::Color(255, 255, 255, 255), 24);
	_uiLayer->addChild(_scoreText);

	_highscoreText = new ScoreText(Vector2<float>(460,16), sf::Color(128, 0, 128, 255), sf::Color(255, 255, 255, 255), 20);
	_uiLayer->addChild(_highscoreText);

	_waveText = new WaveText(Vector2<float>(300,0));
	_uiLayer->addChild(_waveText);
}

void GameScene::createWorld()
{
	//set the world bounds
	float zoom = Application::zoom();
	_screenBoundsMinX = 40;
	_screenBoundsMaxX = (Application::screenWidth() / zoom) - 40;
	_screenBoundsMinY = 40;
	_screenBoundsMaxY = (Application::screenHeight() / zoom) - 40;

	//create tile map
	_tileMap = new TileMap(Vector2<float>(0,0));
	_tileMap->create(Application::screenWidth(), Application::screenHeight(), 32, 32, SPRITE_TILES, TEXTURE_ATLAS_SPRITES, MAP_DATA);
	_tileMapLayer->addChild(_tileMap);

	//create player
	_player = new Player(Vector2<float>(240, 200), *this);
	_gameLayer->addChild(_player);
}

void GameScene::startGame()
{
	//set the current score to 0
	_currentScore = 0;

	//set current wave number to 0
	_currentWaveNumber = 0;

	//set the initial spawn wait time delay
	_initialWaitTime = INITIAL_WAIT_TIME;

	//initialise the state manager
	_gameStateManager.init(this);

	//play game start audio and start the game music
	AudioManager::Get()->playMusic(MUSIC_GAME);
	AudioManager::Get()->playSound(AUDIO_GAME_START);
}

void GameScene::spawnNextWave()
{
	//create a wave data set
	std::vector<EnemyData> enemyDatas = WaveManager::Get()->createWaveDataSet(_currentWaveNumber);
	assert(enemyDatas.size() > 0);

	//reset the total number of enemies to kill this wave
	_totalNumberOfEnemiesInWave = 0;

	//spawn enemies
	std::vector<EnemyData>::iterator enemyDatasIterator, enemyDatasEnd;
	enemyDatasEnd = enemyDatas.end();
	for(enemyDatasIterator = enemyDatas.begin(); enemyDatasIterator != enemyDatasEnd; ++ enemyDatasIterator)
	{
		EnemyData &enemyData = (*enemyDatasIterator);
		spawnEnemy(enemyData.enemyType, enemyData.loot, enemyData.spawnPosition);
	}

	//increase the current wave number
	++ _currentWaveNumber;

	//reset the number of enemies killed this wave to 0
	_numberOfEnemiesKilledInWave = 0;

	//update the hud to display the new wave
	updateHUD();
}

void GameScene::spawnEnemy(unsigned int enemyTypeID, std::vector<LOOT_TYPES> loot, Vector2<float> position)
{
	//create a new enemy instance of the given type
	Enemy* enemy = EnemyTypeDataManager::Get()->createEnemy(enemyTypeID, this, position, loot);

	//spawn the enemy
	enemy->spawn();

	//set the player as the enemies target
	enemy->setTarget(_player);

	//add the enemy to the scene
	_gameLayer->addChild(enemy);

	//increase the number of enemies to destroy this wave
	++ _totalNumberOfEnemiesInWave;
}

void GameScene::spawnLoot(std::vector<LOOT_TYPES> lootTypes, Vector2<float> position)
{
	std::vector<LOOT_TYPES>::iterator lootIterator, lootBegin, lootEnd;
	lootBegin = lootTypes.begin();
	lootEnd = lootTypes.end();
	LOOT_TYPES lootType;
	Collectable* collectable;
	for(lootIterator = lootBegin; lootIterator != lootEnd; ++ lootIterator)
	{
		lootType = (*lootIterator);
		switch(lootType)
		{
			case LOOT_TYPES::WEAPON:
				collectable = new CollectableWeapon(position, *this);
				break;
			case LOOT_TYPES::COINS_1:
				collectable = new CollectableSmallGem(position, *this);
				break;
			case LOOT_TYPES::COINS_2:
				collectable = new CollectableGem(position, *this);
				break;
			case LOOT_TYPES::HEALTH:
				collectable = new CollectableHealth(position, *this);
				break;
		}

		_gameLayer->addChild(collectable);
		collectable->doBounceAnimation();
	}
}

void GameScene::spawnTextIndicator(std::string text, Vector2<float> position, sf::Color &mainColour, sf::Color &borderColour, float textSize)
{
	TextIndicator *textIndicator = new TextIndicator(text, mainColour, borderColour, position, textSize);
	_overObjectsLayer->addChild(textIndicator);
}

void GameScene::spawnNumberIndicator(int value, Vector2<float> position, sf::Color &mainColour, sf::Color &borderColour, bool addPrefixOnPositive)
{
	std::string valueText;

	char buffer[32];
	itoa(value, buffer, 10);

	if(value >= 0 && addPrefixOnPositive)
	{
		valueText = PLUS_SYMBOL + buffer;
	}
	else
	{
		valueText = buffer;
	}

	//determine the text size based on the value
	float absValue = abs(value);
	if(absValue < MIN_INDICATOR_VALUE_SIZE)
	{
		absValue = MIN_INDICATOR_VALUE_SIZE;
	}
	else if(absValue > MAX_INDICATOR_VALUE_SIZE)
	{
		absValue = MAX_INDICATOR_VALUE_SIZE;
	}
	float range = absValue/(MAX_INDICATOR_VALUE_SIZE - MIN_INDICATOR_VALUE_SIZE);
	float textSize = MIN_INDICATOR_TEXT_SIZE + (range*(MAX_INDICATOR_TEXT_SIZE - MIN_INDICATOR_TEXT_SIZE));

	spawnTextIndicator(valueText, position, mainColour, borderColour, textSize);
}

void GameScene::spawnWaveCompleteIndicator()
{
	Vector2<float> position = Vector2<float>(getScreenBoundsMinX() + (getScreenBoundsMaxX() - getScreenBoundsMinX())*0.5, getScreenBoundsMinY() + (getScreenBoundsMaxY() - getScreenBoundsMinY())*0.5 - (Application::zoom()*32));
	TextIndicator *textIndicator = new TextIndicator("Wave Complete!", sf::Color(0, 0, 0, 255), sf::Color(255, 255, 255, 255), position, 100);
	_overObjectsLayer->addChild(textIndicator);

	//play wave complete sound
	AudioManager::Get()->playSound(AUDIO_GAME_START);
}

void GameScene::onEnemyDestroyed(int score, Vector2<float> position)
{
	//increase the player's score
	increaseScore(score);

	//display the score indicator
	spawnNumberIndicator(score, position, sf::Color(255, 255, 255), sf::Color(128, 255, 0), true);

	//increase the kill count for the current wave
	++ _numberOfEnemiesKilledInWave;

	//if the kill count for this wave reaches the kill total number of enemies for this wave then the wave is complete
	if(_numberOfEnemiesKilledInWave >= _totalNumberOfEnemiesInWave && _gameStateManager.currentState() == STATE_NORMAL)
	{
		//change the game state to the wave complete state
		_gameStateManager.changeState(STATE_WAVE_COMPLETE);
	}
}

void GameScene::onEnemyHit(int value, Vector2<float> position, bool critical)
{
	//display the damage indicator
	spawnNumberIndicator(value, position, sf::Color(255, 255, 255), sf::Color(0, 0, 0), false);

	//if the hit was a critical hit then display the critical hit indicator also
	if(critical)
	{
		spawnTextIndicator(CRITICAL, Vector2<float>(position.x, position.y - 20), sf::Color(255, 0, 0, 255), sf::Color(255, 255, 255, 255), 35);
	}

	//shake the screen to signify a hit
	setShakingTime(100);
}

void GameScene::updateHUD()
{
	//update health bar
	_healthBar->setHealthPercentage(_player->currentHealthPercentage());

	//update score text
	_scoreText->setScore(_currentScore);

	//update highscore text, using current score as the value if the current score is higher than the stored highscore
	unsigned int currentHighscoreData = (unsigned int)PlayerData::Get()->getElement(HIGHSCORE);
	if(currentHighscoreData > _currentScore)
	{
		_highscoreText->setScore(currentHighscoreData);
	}
	else
	{
		_highscoreText->setScore(_currentScore);
	}
	
	//update wave
	_waveText->setWave(_currentWaveNumber);
}

void GameScene::onPlayerDestroyed()
{
	//change the game state to the game over state
	_gameStateManager.changeState(STATE_GAME_OVER);
}

void GameScene::increaseScore(int score)
{
	_currentScore += score;
	updateHUD();
}

void GameScene::setShakingTime(float time)
{
	_screenShakingTime = time;
}

SceneLayer* GameScene::gameLayer()
{
	return _gameLayer;
}

SceneLayer* GameScene::underLightLayer()
{
	return _underLightLayer;
}

SceneLayer* GameScene::tileMapLayer()
{
	return _tileMapLayer;
}

SceneLayer* GameScene::overObjectsLayer()
{
	return _overObjectsLayer;
}

SceneLayer* GameScene::uiLayer()
{
	return _uiLayer;
}

Player *GameScene::getPlayer()
{
	return _player;
}

float GameScene::getScreenBoundsMinX()
{
	return _screenBoundsMinX;
}

float GameScene::getScreenBoundsMaxX()
{
	return _screenBoundsMaxX;
}

float GameScene::getScreenBoundsMinY()
{
	return _screenBoundsMinY;
}

float GameScene::getScreenBoundsMaxY()
{
	return _screenBoundsMaxY;
}

float GameScene::getCurrentScore()
{
	return _currentScore;
}