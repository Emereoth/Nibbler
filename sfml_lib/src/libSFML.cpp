#include "../inc/libSFML.hpp"
#include <iostream>

Graphics::Graphics(void) : name(libName::SFML)
{

}

Graphics::~Graphics(void)
{

}

void				Graphics::openWindow(size_t w, size_t h)
{
	_window.create(sf::VideoMode(w, h), "Nibbler (SFML)");
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

Graphics			*create(void)
{
	return new Graphics;
}

void				del(Graphics *test)
{
	delete test;
}
