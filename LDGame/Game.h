#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <functional>
#include <vector>

class Scene;
class SceneData;
class SceneManager;
class AudioManager;
class TextureManager;

struct DelayedCallback
{
	float delay;
	std::function<void()> callback;
};

class Game
{
	public:
		Game(int screenWidth, int screenHeight, float zoom, bool fullscreen, bool fitScreenSize, std::string windowName);
		virtual ~Game();
		void start(unsigned int initialSceneID);
		void onTick();
		void handleEvent(sf::Event inEvent);
		static sf::RenderWindow *window();
		static int screenWidth();
		static int screenHeight();
		static float zoom();
		static void exitGame();
	protected:
		virtual Scene *createScene(unsigned int sceneID, SceneData *sceneData) = 0;
		SceneManager *_sceneManager;
		AudioManager *_audioManager;
		TextureManager *_textureManager;
		Scene* _initialScene;
		sf::Clock _clock;
		static sf::RenderWindow *_window;
		static unsigned int _screenWidth;
		static unsigned int _screenHeight;
		static float _zoom;
		bool _fullscreen;
		bool _fitScreenSize;
		std::string _windowName;
};

#endif