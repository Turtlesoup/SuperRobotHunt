#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneManager.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager* SceneManager::Get()
{
	if(_instance == nullptr)
	{
		_instance = new SceneManager();
	}

	return _instance;
}

SceneManager::SceneManager() : _currentScene(nullptr),
							   _changeScene(false)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::showScene(unsigned int sceneID, SceneData *sceneData)
{
	_currentSceneChangeData.sceneID = sceneID;
	_currentSceneChangeData.sceneData = sceneData;

	_changeScene = true;
}

void SceneManager::onUpdate(float deltaTime)
{
	//if a change scene was requested then change the scene
	if(_changeScene)
	{
		_changeScene = false;

		//dispose and delete the current scene
		if(_currentScene != nullptr)
		{
			_currentScene->onDispose();
			delete _currentScene;
		}

		//create and start the new scene
		_currentScene = _sceneCreationFunction(_currentSceneChangeData.sceneID, _currentSceneChangeData.sceneData);
		if(_currentScene != nullptr)
		{
			_currentScene->onStart();
		}
	}

	//update the current scene if one exists
	if(_currentScene != nullptr)
	{
		_currentScene->onUpdate(deltaTime);
	}
}

void SceneManager::onRender()
{
	if(_currentScene != nullptr)
	{
		_currentScene->onRender();
	}
}

void SceneManager::setSceneCreationFunction(std::function<Scene*(unsigned int, SceneData*)> value)
{
	_sceneCreationFunction = value;
}