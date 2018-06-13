/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:59:48 by rvievill          #+#    #+#             */
/*   Updated: 2018/06/12 17:47:37 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Nibbler.class.hpp"
#include "../inc/Pathfinder.class.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>

Nibbler::Nibbler(const char *pathLib, size_t width, size_t height, float squareSize) :
	manageInput {
		{key::DOWN, &Nibbler::updateEntities},
		{key::UP, &Nibbler::updateEntities},
		{key::LEFT, &Nibbler::updateEntities},
		{key::RIGHT, &Nibbler::updateEntities},
		{key::NO, &Nibbler::updateEntities},
		{key::ONE, &Nibbler::switchLib},
		{key::TWO, &Nibbler::switchLib},
		{key::THREE, &Nibbler::switchLib},
		{key::ESCAPE, &Nibbler::closeLib}
	}
{
	openLib(pathLib, width, height, squareSize);
}

Nibbler::~Nibbler() {}

void				Nibbler::openLib(const char *pathLib, size_t width, size_t height, float squareSize)
{
	void				*entryPoint;
	AGraphics			*(*func)(size_t, size_t, float);
	
	entryPoint = dlopen(pathLib, RTLD_NOW);
	if (!entryPoint)
		throw std::runtime_error(dlerror());
	func = (AGraphics *(*)(size_t, size_t, float))dlsym(entryPoint, "create");
	if (!func)
		throw std::runtime_error(dlerror());
	window = func(width, height, squareSize);
}

void				Nibbler::run(Map &map)
{
	Snake			snake(map);
	Pathfinder		pathfinder(map);
	key				input;

	window->openWindow();
	pathfinder.spawnFood(snake);
	while (window->isOpen())
	{
		if (snake.eatFood)
			pathfinder.spawnFood(snake);
		input = window->keyPress();
		if (!(this->*(manageInput[input]))(snake, input))
			window->draw(map);
		sleep(1);
	}
}

bool				Nibbler::updateEntities(Snake &snake, key key)
{
	if (snake.updatePos(key))
		return (closeLib(snake, key));
	return (false);
}

bool				Nibbler::closeLib(Snake &snake, key key)
{
	static_cast<void>(key);
	static_cast<void>(snake);
	window->closeWindow();
	return (true);
}

bool				Nibbler::switchLib(Snake &snake, key key)
{
	int				name = static_cast<int>(key);

	static_cast<void>(snake);
	static_cast<void>(key);
	if (window->name != name)
	{
		std::cout << "avant => " << window << std::endl;
		closeLib(snake, key);
		if (name == 0)
			openLib("sfml_lib/sfml.so", window->_width, window->_height, window->_squareSize);
		else if (name == 1)
			openLib("sdl_lib/SDL.so", window->_width, window->_height, window->_squareSize);
		else if (name == 2)
			openLib("opengl_lib/openGL.so", window->_width, window->_height, window->_squareSize);
		std::cout <<"apres => " <<  window << std::endl;
		window->openWindow();
	}
	return (false);
}