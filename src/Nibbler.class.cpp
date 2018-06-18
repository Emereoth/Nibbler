/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:59:48 by rvievill          #+#    #+#             */
/*   Updated: 2018/06/18 17:10:10 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Nibbler.class.hpp"
#include "../inc/Pathfinder.class.hpp"
#include "../inc/Time.class.hpp"
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <dlfcn.h>

Nibbler::Nibbler(const char *pathLib, size_t width, size_t height, float squareSize, bool debug) :
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
	},
	_gameSpeed(8),
	_hardMode(false),
	_debug(debug),
	_pathNibbler(getPathNibbler())
{
	(void)_debug;
	openLib(pathLib, width, height, squareSize);
}

Nibbler::~Nibbler() {}

std::string				Nibbler::getPathNibbler()
{
	std::string		pathApp(std::getenv("HOME"));

	return (pathApp + "/Library/nibbler/");
}

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
	time_t			lastRespawn;

	window->openWindow();
	while (window->isOpen())
	{
		if (!_hardMode && snake.size == 10)
		{
			_hardMode = true;
			window->changeMusic();
			_gameSpeed = 4;
			time(&lastRespawn);
		}
		Time::calculDeltaTime();
		if (snake.eatFood || (_hardMode && difftime(time(NULL), lastRespawn) > 8) || pathfinder.food == -1)
		{
			time(&lastRespawn);
			pathfinder.spawnFood(snake);
		}
		input = window->keyPress();
		if (!(this->*(manageInput[input]))(snake, input))
			window->draw(map);
		Time::sleepAsMuchAsNeeded(_gameSpeed);
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
int					name = static_cast<int>(key);
	std::string		lib;

	if (window->name != name)
	{
		closeLib(snake, key);
		if (name == 0)
			lib = _pathNibbler + "sfml_lib/sfml.so";
		else if (name == 1)
			lib = _pathNibbler + "sdl_lib/SDL.so";
		else if (name == 2)
			lib = _pathNibbler + "openGL_lib/openGL.so";
		std::cout << lib << std::endl;
		openLib(lib.c_str(), window->_width, window->_height, window->_squareSize);
		window->openWindow();
		if (_hardMode)
		{
			window->changeMusic();
			_gameSpeed = 4;
		}
	}
	return (false);
}