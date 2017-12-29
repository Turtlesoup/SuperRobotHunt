#include "SpriteBatch.h"
#include <math.h>
 
const int MAX_CAPACITY = 400000;
 
SpriteBatch::SpriteBatch()
{
	_count = 0;
	_capacity = 20000;
	_vertices = new sf::Vertex[_capacity];
 
	_currentBlendMode = sf::BlendAlpha;
}

SpriteBatch::~SpriteBatch()
{
	delete[] _vertices;
	_vertices = NULL;
}

void SpriteBatch::setRenderTarget(sf::RenderTarget &renderTarget)
{
	_renderTarget = &renderTarget;
}

void SpriteBatch::display(bool reset, sf::BlendMode blendMode)
{
	if(_currentBlendMode != blendMode)
	{
		_currentBlendMode = blendMode;
		_state = sf::RenderStates(_currentBlendMode);
	}
	_renderTarget->draw(_vertices, _count * 4, sf::PrimitiveType::Quads, _state);
	_count = 0;
	if(reset)
	{
		_state = sf::RenderStates(_currentBlendMode);
	}
}

void SpriteBatch::draw(const sf::Texture *texture, const Rect<int> &rec, const sf::Color &color, sf::Transform &transform)
{
	if(texture != _state.texture)
    {
		display(false, _currentBlendMode);
		_state.texture = texture;
    }
 
    if(_count*4 >= _capacity)
    {
		display(false, _currentBlendMode);
		if(_capacity < MAX_CAPACITY)
		{
			delete[] _vertices;
			_capacity *= 2;
			if(_capacity > MAX_CAPACITY)
			{
				_capacity = MAX_CAPACITY;
			}
			_vertices = new sf::Vertex[_capacity];
		}
    }

	const float* matrix = transform.getMatrix();
	float pX, pY;
	sf::Vertex v;

    v.color = color;

    pX = 0;
    pY = 0;
    v.position.x = (matrix[0] * pX) + (matrix[4] * pY) + matrix[12];
    v.position.y = (matrix[1] * pX) + (matrix[5] * pY) + matrix[13];
    v.texCoords.x = rec.left;
    v.texCoords.y = rec.top;
    _vertices[_count * 4 + 0] = v;
 
    pX += rec.width;
    v.position.x = (matrix[0] * pX) + (matrix[4] * pY) + matrix[12];
    v.position.y = (matrix[1] * pX) + (matrix[5] * pY) + matrix[13];
    v.texCoords.x += rec.width;
    _vertices[_count * 4 + 1] = v;
 
    pY += rec.height;
    v.position.x = (matrix[0] * pX) + (matrix[4] * pY) + matrix[12];
    v.position.y = (matrix[1] * pX) + (matrix[5] * pY) + matrix[13];
    v.texCoords.y += rec.height;
    _vertices[_count * 4 + 2] = v;
 
    pX -= rec.width;
    v.position.x = (matrix[0] * pX) + (matrix[4] * pY) + matrix[12];
    v.position.y = (matrix[1] * pX) + (matrix[5] * pY) + matrix[13];
    v.texCoords.x -= rec.width;
    _vertices[_count * 4 + 3] = v;
 
    ++ _count;
}