#include "TextureAtlas.h"
#include <assert.h>

#define ASSERT_RESOURCE_EXISTS(resourceURL) assert(_textureRegions.find(resourceURL) != _textureRegions.end());

struct ImageAndResourceURL
{
public:
	ImageAndResourceURL(sf::Image* image, const std::string& resourceURL) : _image(image),
																			_resourceURL(resourceURL)
	{
	}
	sf::Image* getImage()
	{
		return _image;
	}
	std::string getResourceURL()
	{
		return _resourceURL;
	}
private:
	sf::Image* _image;
	std::string _resourceURL;
};

struct sortByWidth
{
	inline bool operator() (ImageAndResourceURL& imageAndURL1, ImageAndResourceURL& imageAndURL2)
	{
		return (imageAndURL1.getImage()->getSize().x > imageAndURL2.getImage()->getSize().x);
	}
};

TextureAtlas::TextureAtlas()
{
}

TextureAtlas::~TextureAtlas()
{
}

Rect<int>& TextureAtlas::getTextureRegion(std::string resourceURL)
{
	ASSERT_RESOURCE_EXISTS(resourceURL);

	return _textureRegions[resourceURL];
}

sf::Texture& TextureAtlas::texture()
{
	return _texture;
}

void TextureAtlas::create(unsigned int width, unsigned int height, const std::vector<std::string> &resourceURLs)
{
	//create texture atlas image
	_textureImage.create(width, height, sf::Color::Transparent);

	unsigned int numResources = resourceURLs.size();

	//create the resource images
	std::vector<ImageAndResourceURL> imagesAndResourceURLs;
	sf::Image* image;
	std::string resourceURL;

	unsigned int resourceIndex;
	for(resourceIndex = 0; resourceIndex < numResources; ++ resourceIndex)
	{
		resourceURL = resourceURLs[resourceIndex];
		image = new sf::Image();
		image->loadFromFile(resourceURL);
		imagesAndResourceURLs.push_back(ImageAndResourceURL(image, resourceURL));
	}

	//sort the images by width
	std::sort(imagesAndResourceURLs.begin(), imagesAndResourceURLs.end(), sortByWidth());

	//copy the resource images, largest width to smallest width by sorting the images by width and copying the pixels
	//of each image to the main image, in a horzontal alignment and continuing the pattern under the lowest portion of
	//the previous row. If the number of images do not fit the sheet, then throw an exception.
	unsigned int currentX = 0;
	unsigned int currentY = 0;
	unsigned int largestHeightInRow = 0;
	sf::Vector2u imageSize;
	for(resourceIndex = 0; resourceIndex < numResources; ++ resourceIndex)
	{
		image = imagesAndResourceURLs[resourceIndex].getImage();
		imageSize = image->getSize();
		resourceURL = imagesAndResourceURLs[resourceIndex].getResourceURL();

		if(currentX + imageSize.x > width)
		{
			currentX = 0;
			currentY += largestHeightInRow;
			largestHeightInRow = 0;
		}

		if(imageSize.y > largestHeightInRow)
		{
			largestHeightInRow = imageSize.y;
		}

		if(currentY + imageSize.y >= height)
		{
			throw std::exception("Too many textures to fit!");
		}

		//copy the image data of the loaded resource to the main texture image
		_textureImage.copy(*image, currentX, currentY);
		//create the texture region for this image segment in the texture atlas
		_textureRegions[resourceURL] = Rect<int>(currentX, currentY, imageSize.x, imageSize.y);

		currentX += imageSize.x;
	}
	
	_texture.loadFromImage(_textureImage);
}

void TextureAtlas::saveToFile(const std::string& filename)
{
	_textureImage.saveToFile(filename);
}