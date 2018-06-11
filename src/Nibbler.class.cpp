/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:59:48 by rvievill          #+#    #+#             */
/*   Updated: 2018/06/11 15:35:57 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Nibbler.class.hpp"
#include "../inc/Pathfinder.class.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>

Nibbler::Nibbler(const char *pathLib, size_t width, size_t height, float squareSize)
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
	// Pathfinder		pathfinder(map);
	key				input;
	int				i = 0;

	window->openWindow();
	while (window->isOpen())
	{
		// if (i % 100 == 0)
			// pathfinder.spawnFood(snake);
		input = window->keyPress();
		std::cout << "input key => " << (int)input << std::endl;
		if (input == key::ESCAPE)
			return ;
		snake.updatePos(input);
		window->draw(map);
		i++;
		sleep(1);
	}
}

void				switchLib(const char *pathLib)
{
	(void)pathLib;
}