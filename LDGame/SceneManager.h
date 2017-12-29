#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <SFML\Graphics.hpp>
#include <functional>

#include "Application.h"

class Scene;
class SceneData;

struct SceneChangeData
{
	unsigned int sceneID;
	SceneData *sceneData;
};

class SceneManager
{
	public:
		static SceneManager* Get();
		SceneManager();
		virtual ~SceneManager();
		void showScene(unsigned int sceneID, SceneData *sceneData = nullptr);
		void onUpdate(float deltaTime);
		void onRender();
		void setSceneCreationFunction(std::function<Scene*(unsigned int, SceneData*)> value);
	private:
		static SceneManager* _instance;
		Scene *_currentScene;
		std::function<Scene*(unsigned int, SceneData*)> _sceneCreationFunction;
		SceneChangeData _currentSceneChangeData;
		bool _changeScene;

};

#endif