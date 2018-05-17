#include "../inc/libSFML.hpp"
#include <iostream>

void				Graphics::run(size_t w, size_t h)
{
	window.create(sf::VideoMode(w, h), "Nibbler (SFML)");
	while (window.isOpen())
	{
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		window.clear(sf::Color::Black);
		sf::RectangleShape square(sf::Vector2f(50, 50));
		sf::Texture	textureSnake;
		textureSnake.loadFromFile("./texture/headRight.png");
		square.setTexture(&textureSnake);
		window.draw(square);
		window.display();
	}
}

Graphics::~Graphics(void)
{

}

Graphics			*create(void)
{
	return new Graphics;
}

void				del(Graphics *test)
{
	delete test;
}
