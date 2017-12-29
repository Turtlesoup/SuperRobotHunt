#include "BaseState.h"
#include "GameStateManager.h"

BaseState::BaseState(GameStateManager *parent) : _parent(parent)
{
}

BaseState::~BaseState()
{
}