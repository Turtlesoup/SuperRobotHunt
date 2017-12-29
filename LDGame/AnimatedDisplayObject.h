#ifndef ANIMATED_DISPLAY_OBJECT_H
#define ANIMATED_DISPLAY_OBJECT_H

#include "SpriteDisplayObject.h"
#include <map>
#include <vector>
#include <functional>

class AnimatedDisplayObject : public SpriteDisplayObject
{
	public:
		AnimatedDisplayObject(const std::string &fileName, const std::string &textureName, Vector2<float> &position, float animationSpeed, Vector2<float> spriteDimensions);
		virtual ~AnimatedDisplayObject();
		virtual void update(float deltaTime);
		void play(const std::string &animationName);
		void stop();
		void addOnAnimationCompleteCallback(const std::function<void()> &onAnimationCompleteCallback);
		void removeOnAnimationCompleteCallback();
		void addAnimation(std::string name, const std::vector<unsigned int> &frames);
	private:
		std::function<void()> _onAnimationCompleteCallback;
		void updateSpriteRect();
		unsigned int _numCols;
		unsigned int _numRows;
		unsigned int _currentCellIndex;
		unsigned int _currentCol;
		unsigned int _currentRow;
		unsigned int _numCells;
		std::vector<unsigned int> _currentAnimationFrames;
		unsigned int _currentAnimationFrameIndex;
		unsigned int _numAnimationFrames;
		std::map<const std::string, std::vector<unsigned int>> _animations;
		bool _animating;
		float _elapsedTime;
		float _animationSpeed;
		Vector2<float> _spriteDimensions;
};

#endif