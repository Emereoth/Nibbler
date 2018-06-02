/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:59:48 by rvievill          #+#    #+#             */
/*   Updated: 2018/06/02 14:19:48 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Nibbler.class.hpp"
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
	key				input;

	window->openWindow();
	while (window->isOpen())
	{
		input = window->keyPress();
		if (input == key::ESCAPE)
			return ;
		window->draw(map);
	}
}

void				switchLib(const char *pathLib)
{
	(void)pathLib;
}