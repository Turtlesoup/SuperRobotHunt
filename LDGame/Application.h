#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include <string>

#include "Game.h"

class Scene;
class SceneData;

extern const std::string GAME_VERSION;

class Application : public Game
{
	public:
		static enum SCENES
		{
			TITLE_SCENE,
			GAME_SCENE
		};
		Application();
		virtual ~Application();
	private:
		Scene* createScene(unsigned int sceneID, SceneData *sceneData);
};

#endif