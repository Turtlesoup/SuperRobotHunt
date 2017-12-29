#include "GameObject.h"
#include "DisplayObject.h"
#include "SpriteDisplayObject.h"
#include "TextDisplayObject.h"
#include "SceneLayer.h"
#include "CollidableObject.h"
#include "QuadTree.h"
#include "Game.h"

SceneLayer::SceneLayer(sf::BlendMode blendMode, bool useRenderTexture) : DisplayObject(Vector2<float>(0, 0)),
																		 _blendMode(blendMode),
																		 _useRenderTexture(useRenderTexture),
																		 _paused(false)
{
	//if using render texture then inistialse the render texture variables
	if(useRenderTexture)
	{
		_renderTexture.create(Game::screenWidth(), Game::screenHeight());
		_renderTextureBlendMode = sf::BlendNone;
		_renderTextureClearColour = sf::Color(0, 0, 0, 255);
		_renderTextureSmooth = false;
	}
}

SceneLayer::~SceneLayer()
{
}

void SceneLayer::update(float deltaTime)
{
	if(!_paused)
	{
		DisplayObject::update(deltaTime);
	}
}

void SceneLayer::render(SpriteBatch &spriteBatch, sf::Transform &transform)
{
	if(_useRenderTexture)
	{
		_renderTexture.setSmooth(_renderTextureSmooth);
		_renderTexture.clear(_renderTextureClearColour);
		_spriteBatch.setRenderTarget(_renderTexture);
	}
	else
	{
		_spriteBatch.setRenderTarget(*Game::window());
	}

	transform.translate(_position.x - _origin.x + _offset.x, _position.y - _origin.y + _offset.y);

	//render the children game objects
	GameObject::render(_spriteBatch, transform);

	transform.translate(-_position.x + _origin.x - _offset.x, -_position.y + _origin.y - _offset.y);

	_spriteBatch.display(true, _blendMode);

	//if we are using a render texture then we must
	//render the render texture to the target window
	if(_useRenderTexture)
	{
		_renderTexture.display();
		_renderTextureSprite.setTexture(_renderTexture.getTexture());

		Game::window()->draw(_renderTextureSprite, _renderTextureBlendMode);
	}
}

void SceneLayer::addChild(GameObject *gameObject)
{
	_gameObjects.push_back(gameObject);
	gameObject->onAdded(this, this);
}

void SceneLayer::setRenderTextureBlendMode(const sf::BlendMode& blendMode)
{
	_renderTextureBlendMode = blendMode;
}

void SceneLayer::setRenderTextureClearColour(const sf::Color& colour)
{
	_renderTextureClearColour = colour;
}

void SceneLayer::setRenderTextureSmooth(bool value)
{
	_renderTextureSmooth = value;
}

void SceneLayer::pause(bool paused)
{
	_paused = paused;
}