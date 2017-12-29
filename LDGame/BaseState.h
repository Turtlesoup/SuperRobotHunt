#ifndef BASE_STATE_H
#define BASE_STATE_H

class GameStateManager;

enum GAME_STATE
{
	STATE_NONE,
	STATE_NORMAL,
	STATE_PAUSED,
	STATE_WAVE_COMPLETE,
	STATE_GAME_OVER
};

class BaseState
{
	public:
		BaseState(GameStateManager *parent);
		virtual ~BaseState();
		virtual void onStart(GAME_STATE previousState) = 0;
		virtual void onUpdate(float deltaTime) = 0;
		virtual void onQuit() = 0;
	protected:
		GameStateManager *_parent;
};

#endif