#include "../inc/libSFML.hpp"
#include <iostream>

Graphics::Graphics(size_t width, size_t height, float squareSize) : name(libName::SFML)
{
	_height = height;
	_width = width;
	_squareSize = squareSize;
	_spriteMap =
	{
		{sprite::HEAD_UP, "./texture/headUp.png"},
		{sprite::HEAD_DOWN, "./texture/headDown.png"},
		{sprite::HEAD_LEFT, "./texture/headLeft.png"},
		{sprite::HEAD_RIGHT, "./texture/headRight.png"},
		{sprite::BODY_H, "./texture/bodyH.png"},
		{sprite::BODY_V, "./texture/bodyV.png"},
		{sprite::TAIL_UP, "./texture/tailUp.png"},
		{sprite::TAIL_DOWN, "./texture/tailDown.png"},
		{sprite::TAIL_LEFT, "./texture/tailLeft.png"},
		{sprite::TAIL_RIGHT, "./texture/tailRight.png"},
		{sprite::BODY_UP_LEFT, "./texture/bodyUpLeft.png"},
		{sprite::BODY_UP_RIGHT, "./texture/bodyUpRight.png"},
		{sprite::BODY_DOWN_LEFT, "./texture/bodyDownLeft.png"},
		{sprite::BODY_DOWN_RIGHT, "./texture/bodyDownRight.png"},
		{sprite::WALL, "./texture/wall.png"},
		{sprite::FOOD, "./texture/apple.png"}
	};
}

Graphics::~Graphics(void)
{

}

void				Graphics::openWindow(void)
{
	_window.create(sf::VideoMode(_width, _height), "Nibbler (SFML)");
	_window.setKeyRepeatEnabled(false);
	runSound();
}

bool				Graphics::isOpen(void) const
{
	return (_window.isOpen());
}

key					Graphics::keyPress(void)
{
	_window.pollEvent(_event);
	return (key::NO);
}

void				Graphics::draw(Map &map)
{
	float			spaceAroundX = (_width / 2) - (_squareSize * 31);

	for (size_t y = 0; y < 62; y++)
	{
		for(size_t x = 0; x < 62; x++)
		{
			if (map.map[y][x] == '1')
			{
				float			width = spaceAroundX + (x * _squareSize);
				float			height = y * _squareSize;
				sf::Sprite		sprite;
				sf::Texture		tex;

				tex.setSmooth(true);
				tex.loadFromFile(_spriteMap[sprite::WALL]);	
				sprite.setTexture(tex);
				sprite.setPosition(width, height);

				float			widthSprite = sprite.getLocalBounds().width;
				float			heightSprite = sprite.getLocalBounds().height;

				sprite.setScale(_squareSize / widthSprite, _squareSize / heightSprite);
				_window.draw(sprite);
			}
		}
	}
	_window.display();
}

void				Graphics::runSound(void)
{
	_music.openFromFile("./music/tetris.wav");
	_music.setLoop(true);
	_music.play();
}

void				Graphics::closeWindow(void)
{
	_window.close();
}

Graphics			*create(size_t width, size_t height, float squareSize)
{
	return new Graphics(width, height, squareSize);
}

void				del(Graphics *test)
{
	delete test;
}
