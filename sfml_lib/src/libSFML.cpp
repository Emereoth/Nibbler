#include "../inc/libSFML.hpp"
#include <iostream>

Graphics::~Graphics(void)
{

}

void				Graphics::run(size_t w, size_t h)
{
	sf::Music music;
	music.openFromFile("./music/tetris.wav");
	music.setLoop(true);
	music.play();
	openWindow(w, h);
}

void				Graphics::openWindow(size_t w, size_t h)
{
	_window.create(sf::VideoMode(w, h), "Nibbler (SFML)");

	sf::RectangleShape square(sf::Vector2f(SIZE_SQUARE, SIZE_SQUARE));
	sf::Texture	textureSnake;
	textureSnake.loadFromFile("./texture/headRight.png");
	square.setTexture(&textureSnake);
	square.setOrigin(SIZE_SQUARE, 0);
    square.setPosition(SIZE_SQUARE, 0);
	_window.setFramerateLimit(100);
	_window.setKeyRepeatEnabled(false);
	while (_window.isOpen())
	{
		sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
				_window.close();
	        while (_window.pollEvent(event));
        }
		square.move(1, 0);
		_window.clear(sf::Color::Black);
		_window.draw(square);
		_window.display();
	}
}

Graphics			*create(void)
{
	return new Graphics;
}

void				del(Graphics *test)
{
	delete test;
}
