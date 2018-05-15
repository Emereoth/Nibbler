#include "../inc/libSFML.hpp"
#include <iostream>

void				Graphics::openWindow(size_t w, size_t h)
{
	window.create(sf::VideoMode(w, h), "test nibbler");
	while (window.isOpen())
	{
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
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
