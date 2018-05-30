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
	size_t			size = 62 * 62;
	int				pos = 0;
	float			widthSprite;
	float			heightSprite;
	float			posX;
	float			posY;

	for (size_t i = 0; i < size; i++)
	{
		if (pos == map.offsetMap)
			pos = 0;
		if (map.map[i] == 1)
		{
			posX = spaceAroundX + (pos * _squareSize);
			posY = (i / 62) * _squareSize;
			_texture.setSmooth(true);
			_texture.loadFromFile(_spriteMap[sprite::WALL]);	
			_sprite.setTexture(_texture);
			_sprite.setPosition(posX, posY);
			widthSprite = _sprite.getLocalBounds().width;
			heightSprite = _sprite.getLocalBounds().height;
			_sprite.setScale(_squareSize / widthSprite, _squareSize / heightSprite);
			_window.draw(_sprite);
		}
		pos++;
	}
	_window.display();
}

void				Graphics::runSound(void)
{
	_music.openFromFile("./music/tetris_hard.wav");
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
