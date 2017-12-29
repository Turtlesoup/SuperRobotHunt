#ifndef SCENE_LAYER_H
#define SCENE_LAYER_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "SpriteBatch.h"
#include "DisplayObject.h"
#include "CollisionManager.h"

class GameObject;

class SceneLayer : public DisplayObject
{
	public:
		SceneLayer(sf::BlendMode blendMode, bool useRenderTexture = false);
		~SceneLayer();
		virtual void update(float deltaTime);
		virtual void render(SpriteBatch &spriteBatch, sf::Transform &transform);
		virtual void addChild(GameObject *gameObject);
		void setRenderTextureBlendMode(const sf::BlendMode& blendMode);
		void setRenderTextureClearColour(const sf::Color& colour);
		void setRenderTextureSmooth(bool value);
		void pause(bool paused);
	protected:
		SpriteBatch _spriteBatch;
	private:
		sf::BlendMode _blendMode;
		bool _useRenderTexture;
		sf::RenderTexture _renderTexture;
		sf::Sprite _renderTextureSprite;
		sf::BlendMode _renderTextureBlendMode;
		sf::Color _renderTextureClearColour;
		bool _renderTextureSmooth;
		bool _paused;
};

#endif