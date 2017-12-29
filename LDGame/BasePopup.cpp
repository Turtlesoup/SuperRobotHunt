#include "BasePopup.h"
#include "GuiManager.h"
#include "ButtonGuiWidget.h"

BasePopup::BasePopup(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::string popupWidgetID) : DisplayObject(offScreenPosition),
																													 _onScreenPosition(onScreenPosition),
																													 _offScreenPosition(offScreenPosition),
																													 _currentCurveValue(0),
																													 _showingAnimation(false),
																													 _hidingAnimation(false),
																													 _isShowing(false),
																													 SPEED(0.002),
																													 BOUNCE_HEIGHT(100)
{
	_popupWidget = GuiManager::Get()->createLayout(popupWidgetID);
	_buttons = GuiManager::Get()->getWidgetsOfType(WIDGET_BUTTON, _popupWidget);

	addChild(_popupWidget);

	_bounceTween.getP1().x = _offScreenPosition.x;
	_bounceTween.getP1().y = _offScreenPosition.y;

	_bounceTween.getP2().x = _onScreenPosition.x;
	_bounceTween.getP2().y = _onScreenPosition.y - BOUNCE_HEIGHT;

	_bounceTween.getP3().x = _onScreenPosition.x;
	_bounceTween.getP3().y = _onScreenPosition.y - BOUNCE_HEIGHT;

	_bounceTween.getP4().x = _onScreenPosition.x;
	_bounceTween.getP4().y = _onScreenPosition.y;
}

BasePopup::~BasePopup()
{
}

void BasePopup::update(float deltaTime)
{
	if(_showingAnimation)
	{
		_currentCurveValue += deltaTime * SPEED;

		Vector2<float> newPosition = _bounceTween.getPoint(_currentCurveValue);

		setX(newPosition.x);
		setY(newPosition.y);

		if(_currentCurveValue >= 1)
		{
			_showingAnimation = false;
		}
	}
	else if(_hidingAnimation)
	{
		_currentCurveValue -= deltaTime * SPEED;

		Vector2<float> newPosition = _bounceTween.getPoint(_currentCurveValue);

		setX(newPosition.x);
		setY(newPosition.y);

		if(_currentCurveValue <= 0)
		{
			_hidingAnimation = false;
			_isShowing = false;
		}
	}
}

void BasePopup::showPopup()
{
	_showingAnimation = true;
	_hidingAnimation = false;

	_isShowing = true;

	_currentCurveValue = 0.0;

	setX(_offScreenPosition.x);
	setY(_offScreenPosition.y);
}

void BasePopup::hidePopup()
{
	//deselect all buttons
	std::vector<BaseGuiWidget*>::iterator buttonsIter, buttonsEnd;
	buttonsEnd = _buttons.end();
	for(buttonsIter = _buttons.begin(); buttonsIter != buttonsEnd; buttonsIter++)
	{
		static_cast<ButtonGuiWidget*>(*buttonsIter)->onDeselected();
	}

	_hidingAnimation = true;
	_showingAnimation = false;

	_currentCurveValue = 1.0;

	setX(_onScreenPosition.x);
	setY(_onScreenPosition.y);
}

bool BasePopup::isShowing()
{
	return _isShowing;
}