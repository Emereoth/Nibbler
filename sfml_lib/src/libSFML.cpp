#include "../inc/libSFML.hpp"
#include <iostream>

Graphics::Graphics(size_t width, size_t height, size_t squareSize) : name(libName::SFML)
{
	_width = width;
	_height = height;
	_squareSize = squareSize;
	_spriteMap[16] =
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

void				Graphics::draw(void)
{

}

void				Graphics::runSound(void) const
{
	sf::Music music;
	music.openFromFile("./music/tetris.wav");
	music.setLoop(true);
	music.play();
}

Graphics			*create(size_t width, size_t height, size_t squareSize)
{
	return new Graphics(width, height, squareSize);
}

void				del(Graphics *test)
{
	delete test;
}
