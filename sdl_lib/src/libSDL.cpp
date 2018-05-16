/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:54 by acottier          #+#    #+#             */
/*   Updated: 2018/05/16 18:06:38 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../SDL/include/SDL.h"
#include "../inc/libSDL.h"

void		Graphics::openWindow(size_t w, size_t h)
{
	SDL_Window	*win;
	SDL_Event	currentEvent;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindow("Nibbler (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_MOUSE_FOCUS);
	while (SDL_PollEvent(&currentEvent))
	{
		SDL_PumpEvents();
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
			SDL_DestroyWindow(win);
	}
	SDL_Quit();
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