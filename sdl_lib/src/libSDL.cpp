/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:54 by acottier          #+#    #+#             */
/*   Updated: 2018/05/17 18:32:17 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libSDL.hpp"
#include <iostream>

void		Graphics::run(size_t w, size_t h)
{
	SDL_Window	*win;
	SDL_Event	currentEvent;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL init error :" << SDL_GetError() << std::endl;
		return ;
	}
	win = SDL_CreateWindow("Nibbler (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_MOUSE_FOCUS);
	while (win)
	{
		while (SDL_PollEvent(&currentEvent))
		{
			SDL_PumpEvents();
			drawImage("../test.png", win);
			if (currentEvent.type == SDL_WINDOWEVENT && currentEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				SDL_DestroyWindow(win);
				win = NULL;
			}
		}
	}
	SDL_Quit();
}

Graphics::drawImage(std::string const & path, SDL_Window * win)
{
	int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }
    else
    {
        //Get window surface
        gScreenSurface = SDL_GetWindowSurface( gWindow );
    }
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