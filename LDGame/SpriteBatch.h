#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include "Rect.h"
#include <SFML\Graphics.hpp>

class SpriteBatch
{
	public:
		SpriteBatch();
		~SpriteBatch();
		void setRenderTarget(sf::RenderTarget &renderTarget);
		void display(bool reset = true, sf::BlendMode blendMode = sf::BlendAlpha);
		void draw(const sf::Texture *texture, const Rect<int> &rec, const sf::Color &color, sf::Transform &transform);
	private:
		sf::RenderTarget *_renderTarget;
		sf::RenderStates _state;
		sf::Vertex *_vertices;
		sf::BlendMode _currentBlendMode;
		int _count;
		int _capacity;
};

#endif