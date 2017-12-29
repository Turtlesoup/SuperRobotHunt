#include "GameOverPanel.h"
#include "EventManager.h"
#include "BaseGuiWidget.h"
#include "ButtonGuiWidget.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "GuiManager.h"
#include "Resources.h"
#include "AudioManager.h"

const std::string RETRY_BUTTON_ID = "2";
const std::string QUIT_BUTTON_ID = "6";

GameOverPanel::GameOverPanel(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::function<void()> onRetryPressedCallback, std::function<void()> onQuitPressedCallback) : BasePopup(onScreenPosition, offScreenPosition, GUI_JSON_GAME_OVER_PANEL),
																																													   KeyListener(),
																																													   _currentSelectedButtonIndex(0),
																																													   _onRetryPressedCallback(onRetryPressedCallback),
																																													   _onQuitPressedCallback(onQuitPressedCallback),
																																													   _selectKeyPressed(false),
																																													   _directionKeyPressed(false)
{
	_retryButton = GuiManager::Get()->getWidgetWithID(RETRY_BUTTON_ID, _popupWidget);
	_quitButton = GuiManager::Get()->getWidgetWithID(QUIT_BUTTON_ID, _popupWidget);
}

GameOverPanel::~GameOverPanel()
{
}

void GameOverPanel::showPopup()
{
	BasePopup::showPopup();

	_currentSelectedButtonIndex = 0;
	static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onSelected();

	_directionKeyPressed = false;
}

void GameOverPanel::onKeyPressed(EventData *eventData)
{
	KeyPressedEventData *keyPressedEventData = dynamic_cast<KeyPressedEventData*>(eventData);
	if(keyPressedEventData != nullptr)
	{
		switch(keyPressedEventData->getKeycode())
		{
			case sf::Keyboard::X:
				static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onPressed();
				_selectKeyPressed = true;
				break;
			case sf::Keyboard::Right:
			case sf::Keyboard::Left:
				_directionKeyPressed = true;
				break;
		}
	}
}

void GameOverPanel::onKeyReleased(EventData *eventData)
{
	KeyReleasedEventData *keyReleasedEventData = dynamic_cast<KeyReleasedEventData*>(eventData);
	if(keyReleasedEventData != nullptr)
	{
		switch(keyReleasedEventData->getKeycode())
		{
			case sf::Keyboard::X:
				if(_selectKeyPressed)
				{
					if(_buttons[_currentSelectedButtonIndex] == _retryButton)
					{
						_onRetryPressedCallback();
					}
					else if(_buttons[_currentSelectedButtonIndex] == _quitButton)
					{
						_onQuitPressedCallback();
					}
					static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onRelease();
					AudioManager::Get()->playSound(AUDIO_BUTTON_RELEASED);
					_selectKeyPressed = false;
				}
				break;
			case sf::Keyboard::Left:
				if(_directionKeyPressed)
				{
					static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onDeselected();
					if(_currentSelectedButtonIndex == 0)
					{
						_currentSelectedButtonIndex = 0;
					}
					else
					{
						-- _currentSelectedButtonIndex;
					}
					static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onSelected();
					_directionKeyPressed = false;
				}
				break;
			case sf::Keyboard::Right:
				if(_directionKeyPressed)
				{
					static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onDeselected();
					if(_currentSelectedButtonIndex >= _buttons.size() - 1)
					{
						_currentSelectedButtonIndex = _buttons.size() - 1;
					}
					else
					{
						++ _currentSelectedButtonIndex;
					}
					static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onSelected();
					_directionKeyPressed = false;
				}
				break;
		}
	}
}