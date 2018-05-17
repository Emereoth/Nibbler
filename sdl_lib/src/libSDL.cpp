/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:54 by acottier          #+#    #+#             */
/*   Updated: 2018/05/17 15:24:44 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../SDL/include/SDL.h"
#include "../inc/libSDL.hpp"
#include <iostream>

void		Graphics::openWindow(size_t w, size_t h)
{
	SDL_Window	*win;
	SDL_Event	currentEvent;

	if (SDL_Init(SDL_INIT_VIDEO))
		std::cout << "lol" << std::endl;
	win = SDL_CreateWindow("Nibbler (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_MOUSE_FOCUS);
	while (win)
	{
		while (SDL_PollEvent(&currentEvent))
		{
			SDL_PumpEvents();
			if (currentEvent.type == SDL_WINDOWEVENT && currentEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				SDL_DestroyWindow(win);
				win = NULL;
			}
		}
	}
	SDL_Quit();
}

Graphics::Graphics(void)
{
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