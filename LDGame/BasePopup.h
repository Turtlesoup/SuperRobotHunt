#ifndef BASE_POPUP_H
#define BASE_POPUP_H

#include "DisplayObject.h"
#include "BaseGuiWidget.h"
#include "CubicBezierCurve.h"

class BasePopup : public DisplayObject
{
	public:
		BasePopup(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::string popupWidgetID);
		virtual ~BasePopup();
		virtual void update(float deltaTime);
		virtual void showPopup();
		virtual void hidePopup();
		virtual bool isShowing();
	protected:
		BaseGuiWidget *_popupWidget;
		std::vector<BaseGuiWidget*> _buttons;
		Vector2<float> _onScreenPosition;
		Vector2<float> _offScreenPosition;
		CubicBezierCurve _bounceTween;
		float _currentCurveValue;
		bool _showingAnimation;
		bool _hidingAnimation;
		bool _isShowing;
		const float SPEED;
		const float BOUNCE_HEIGHT;
};

#endif