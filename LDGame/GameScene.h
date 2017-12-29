#ifndef GAME_SCENE_h
#define GAME_SCENE_h

#include "Scene.h"
#include "GameStateManager.h"
#include "GuiManager.h"
#include "LootTypes.h"
#include "Vector2.h"
#include "BitmapFont.h"

class Player;
class EventData;
class SceneLayer;
class Light;
class FlickeringLight;
class TileMap;
class TextDisplayObject;
class EventData;
class HealthBar;
class ScoreText;
class WaveText;

class GameScene : public Scene
{
	public:
		GameScene(SceneData *sceneData = 0);
		~GameScene();
		void onStart();
		void onUpdate(float deltaTime);
		void onDispose();
		void createLayers();
		void createHUD();
		void createWorld();
		void startGame();
		void spawnNextWave();
		void spawnEnemy(unsigned int enemyTypeID, std::vector<LOOT_TYPES> loot, Vector2<float> position);
		void spawnLoot(std::vector<LOOT_TYPES> lootTypes, Vector2<float> position);
		void spawnTextIndicator(std::string text, Vector2<float> position, sf::Color &mainColour, sf::Color &borderColour, float textSize);
		void spawnNumberIndicator(int value, Vector2<float> position, sf::Color &mainColour, sf::Color &borderColour, bool addPrefixOnPositive);
		void spawnWaveCompleteIndicator();
		void onEnemyDestroyed(int score, Vector2<float> position);
		void onEnemyHit(int value, Vector2<float> position, bool critical);
		void updateHUD();
		void onPlayerDestroyed();
		void increaseScore(int score);
		void setShakingTime(float time);
		SceneLayer *gameLayer();
		SceneLayer *tileMapLayer();
		SceneLayer *underLightLayer();
		SceneLayer *overObjectsLayer();
		SceneLayer *uiLayer();
		Player *getPlayer();
		float getScreenBoundsMinX();
		float getScreenBoundsMaxX();
		float getScreenBoundsMinY();
		float getScreenBoundsMaxY();
		float getCurrentScore();
	private:
		GameStateManager _gameStateManager;
		Player *_player;
		SceneLayer *_gameLayer;
		SceneLayer *_tileMapLayer;
		SceneLayer *_underLightLayer;
		SceneLayer *_overObjectsLayer;
		SceneLayer *_uiLayer;
		TileMap *_tileMap;
		HealthBar *_healthBar;
		ScoreText *_scoreText;
		ScoreText *_highscoreText;
		WaveText *_waveText;
		float _screenBoundsMinX;
		float _screenBoundsMaxX;
		float _screenBoundsMinY;
		float _screenBoundsMaxY;
		const float MIN_INDICATOR_TEXT_SIZE;
		const float MAX_INDICATOR_TEXT_SIZE;
		const float MIN_INDICATOR_VALUE_SIZE;
		const float MAX_INDICATOR_VALUE_SIZE;
		const float INITIAL_WAIT_TIME;
		unsigned int _currentScore;
		unsigned int _currentWaveNumber;
		unsigned int _totalNumberOfEnemiesInWave;
		unsigned int _numberOfEnemiesKilledInWave;
		float _screenShakingTime;
		float _initialWaitTime;
};

#endif