/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:59:48 by rvievill          #+#    #+#             */
/*   Updated: 2018/06/08 16:01:21 by acottier         ###   ########.fr       */
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
	Pathfinder		pathfinder(map);
	key				input;
	int				i = 0;

	window->openWindow();
	while (window->isOpen())
	{
		if (i % 100 == 0)
			pathfinder.spawnFood(snake);
		input = window->keyPress();
		if (input == key::ESCAPE)
			return ;
		window->draw(map);
		i++;
	}
}

void				switchLib(const char *pathLib)
{
	(void)pathLib;
}