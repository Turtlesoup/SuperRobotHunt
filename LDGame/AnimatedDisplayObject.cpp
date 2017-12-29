#include "AnimatedDisplayObject.h"
#include "Application.h"
#include <cmath>

AnimatedDisplayObject::AnimatedDisplayObject(const std::string &fileName, const std::string &textureName, Vector2<float> &position, float animationSpeed, Vector2<float> spriteDimensions) : SpriteDisplayObject(fileName, textureName, position)
{
	_animationSpeed = animationSpeed;
	_spriteDimensions = spriteDimensions;
	_numCols = ceil(_textureRegion.width / spriteDimensions.x);
	_numRows = ceil(_textureRegion.height / spriteDimensions.y);
	_numCells = _numCols * _numRows;
	_currentCellIndex = 0;
	_currentCol = 0;
	_currentRow = 0;
	_spriteRect = Rect<int>(_textureRegion.left, _textureRegion.top, spriteDimensions.x, spriteDimensions.y);
	_elapsedTime = 0.0f;
	_animating = false;

	//update the width, height and origin
	_width = _spriteDimensions.x;
	_height = _spriteDimensions.y;
	_origin.x = _width*0.5;
	_origin.y = _height*0.5;
}

AnimatedDisplayObject::~AnimatedDisplayObject()
{
}

void AnimatedDisplayObject::play(const std::string& animationName)
{
	_animating = true;
	_elapsedTime = 0.0f;

	_currentAnimationFrames = _animations[animationName];
	_currentAnimationFrameIndex = 0;
	_numAnimationFrames = _currentAnimationFrames.size();

	updateSpriteRect();
}

void AnimatedDisplayObject::addOnAnimationCompleteCallback(const std::function<void()> &onAnimationCompleteCallback)
{
	_onAnimationCompleteCallback = onAnimationCompleteCallback;
}

void AnimatedDisplayObject::removeOnAnimationCompleteCallback()
{
	if(_onAnimationCompleteCallback)
	{
		_onAnimationCompleteCallback = std::function<void()>();
	}
}

void AnimatedDisplayObject::stop()
{
	_animating = false;
}

void AnimatedDisplayObject::addAnimation(std::string name, const std::vector<unsigned int> &frames)
{
	_animations[name] = frames;
}

void AnimatedDisplayObject::update(float deltaTime)
{
	DisplayObject::update(deltaTime);

	if(_animating)
	{
		_elapsedTime += deltaTime;
		if(_elapsedTime >= _animationSpeed)
		{
			//update the cell index for the current animation
			_currentAnimationFrameIndex++;
			if(_currentAnimationFrameIndex >= _numAnimationFrames)
			{
				_currentAnimationFrameIndex = 0;

				//if an animation complete callback has been set then call the callback here
				if(_onAnimationCompleteCallback)
				{
					_onAnimationCompleteCallback();
				}
			}

			updateSpriteRect();

			//reset the elapsed time
			_elapsedTime = 0.0f;
		}
	}
}

void AnimatedDisplayObject::updateSpriteRect()
{
	//set the current cell index based on the animation frame and set the sprite's texture rectangle
	_currentCellIndex = _currentAnimationFrames[_currentAnimationFrameIndex];
	_currentCol = _currentCellIndex % _numCols;
	if(_numRows == 1)
	{
		_currentRow = 0;
	}
	else
	{
		_currentRow = _currentCellIndex / _numCols;
	}
	_spriteRect = Rect<int>(_textureRegion.left + (_currentCol * _spriteDimensions.x), _textureRegion.top + (_currentRow * _spriteDimensions.y), _spriteDimensions.x, _spriteDimensions.y);
}