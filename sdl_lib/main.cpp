/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 10:30:47 by acottier          #+#    #+#             */
/*   Updated: 2018/05/16 18:02:15 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL/include/SDL.h"

int			main()
{
	SDL_Window	*window = NULL;
	SDL_Surface	*surface = NULL;
	SDL_Event	event;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("Woopsie, error: %s\n", SDL_GetError());
	else
	{
		window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_MOUSE_FOCUS);
		surface = SDL_GetWindowSurface(window);
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 16, 16, 16));
		SDL_UpdateWindowSurface(window);
		while (1)
		{
			while (SDL_PollEvent(&event))
			{	
		   		SDL_PumpEvents();
				if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					SDL_DestroyWindow(window);
					SDL_Quit();
					return (0);
				}
			}
		}
		SDL_Quit();
	}
	return (0);
}