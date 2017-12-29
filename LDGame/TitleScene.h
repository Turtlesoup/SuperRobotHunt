#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "Scene.h"
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>

class EventData;
class DisplayObject;
class TextDisplayObject;
class SpriteDisplayObject;
class TitlePanel;
class OptionsPopup;

class TitleScene : public Scene
{
	public:
		TitleScene(SceneData *sceneData = 0);
		~TitleScene();
		void onStart();
		void onUpdate(float deltaTime);
		void onDispose();
		void onKeyPressed(sf::Keyboard::Key key);
	private:
		void startGame();
		void showOptions();
		void onOptionsPopupClosed();
		DisplayObject *_button;
		SpriteDisplayObject *_background;
		TextDisplayObject *_textbox;
		sf::Font _font;
		TitlePanel *_titlePanel;
		OptionsPopup *_optionsPopup;
};

#endif