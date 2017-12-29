#include "TextureManager.h"
#include "TextureAtlas.h"
#include "SceneManager.h"
#include "SceneData.h"
#include "AudioManager.h"
#include "EventManager.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "SFMLEventData.h"
#include "Game.h"

unsigned int Game::_screenWidth = 0;
unsigned int Game::_screenHeight = 0;
float Game::_zoom = 0.0f;
sf::RenderWindow *Game::_window = 0;

Game::Game(int screenWidth, int screenHeight, float zoom, bool fullscreen, bool fitScreenSize, std::string windowName) : _fullscreen(fullscreen),
																														 _windowName(windowName),
																														 _fitScreenSize(fitScreenSize)
{
	if(_fitScreenSize)
	{
		sf::VideoMode destopVideoMode = sf::VideoMode::getDesktopMode();
		_screenWidth = destopVideoMode.width;
		_screenHeight = destopVideoMode.height;
	}
	else
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
	}

	_zoom = zoom;

	_sceneManager = SceneManager::Get();
	_audioManager = AudioManager::Get();
	_textureManager = TextureManager::Get();

	//set the scene managers scene creation function
	_sceneManager->setSceneCreationFunction(std::bind<Scene*>(&Game::createScene, this, std::placeholders::_1, std::placeholders::_2));
}

Game::~Game()
{
}

void Game::start(unsigned int initialSceneID)
{
	if(_fitScreenSize)
	{
		if(_fullscreen)
		{
			_window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), _windowName, sf::Style::Fullscreen);
		}
		else
		{
			_window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), _windowName, sf::Style::Default);
		}
	}
	else
	{
		if(_fullscreen)
		{
			_window = new sf::RenderWindow(sf::VideoMode(screenWidth(), screenHeight()), _windowName, sf::Style::Fullscreen);
		}
		else
		{
			_window = new sf::RenderWindow(sf::VideoMode(screenWidth(), screenHeight()), _windowName, sf::Style::Default);
		}
	}
	
	_sceneManager->showScene(initialSceneID);
	_clock.restart();

	sf::Event event;

	while(_window->isOpen())
	{
		_window->clear(sf::Color::Black);

		if(_window->pollEvent(event))
		{
			handleEvent(event);
		}
		
		onTick();
		_window->display();
	}
	
	delete _window;
}

void Game::onTick()
{
	float deltaTime = _clock.restart().asMilliseconds();

	_sceneManager->onUpdate(deltaTime);
	_sceneManager->onRender();
}

void Game::handleEvent(sf::Event event)
{
	switch(event.type)
	{
		case sf::Event::EventType::KeyPressed:
			EventManager::Get()->dispatchEvent(EVENT_TYPES::KEY_PRESSED, new KeyPressedEventData(event.key.code));
			break;
		case sf::Event::EventType::KeyReleased:
			EventManager::Get()->dispatchEvent(EVENT_TYPES::KEY_RELEASED, new KeyReleasedEventData(event.key.code));
			break;
		case sf::Event::Closed:
			_window->close();
			break;
		default:
			EventManager::Get()->dispatchEvent(EVENT_TYPES::SFML_EVENT, new SFMLEventData(event));
			break;
	}
}

sf::RenderWindow *Game::window()
{
	return _window;
}

int Game::screenWidth()
{
	return _screenWidth;
}

int Game::screenHeight()
{
	return _screenHeight;
}

float Game::zoom()
{
	return _zoom;
}

void Game::exitGame()
{
	_window->close();
}