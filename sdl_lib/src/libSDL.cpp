/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:54 by acottier          #+#    #+#             */
/*   Updated: 2018/05/22 17:07:46 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libSDL.hpp"
#include <iostream>

void			Graphics::openWindow(size_t w, size_t h)
{
	SDL_Window	*win;
	SDL_Surface	*newSurface = NULL;
	SDL_Rect	dst;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDL init error :" << SDL_GetError() << std::endl;
		return ;
	}
	win = SDL_CreateWindow("Nibbler (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_MOUSE_FOCUS);
	newSurface = drawImage((char *)"../texture/headUp.png", win);
	dst.x = 0;
	dst.y = 0;
	dst.w = SIZE_SQUARE;
	dst.h = SIZE_SQUARE;
	if (SDL_BlitScaled(newSurface, NULL, SDL_GetWindowSurface(win), &dst)!= 0)
		std::cerr << "SDL blit transfer error: " << SDL_GetError() << std::endl;
	setMusic();
	loop(win);
	SDL_Quit();
}

void			Graphics::setMusic()
{
	Mix_Chunk	*soundtrack;
	// SDL_AudioSpec	*audio;
	// SDL_AudioSpec	wav_spec;
	// Uint8			*wav_buffer;
	// Uint32			wav_length;

	// if (!(audio = SDL_LoadWAV("../music/towerfall.wav", &wav_spec, &wav_buffer, &wav_length)))
	// 	std::cerr << "Error loading WAV: " << SDL_GetError() << std::endl;
	// if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
	// 	fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
	// 	exit(-1);
	// }
	// SDL_PauseAudio(0);
	if (!Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024))
	{
		std::cerr << "Error loading SDL_Mixer: " << Mix_GetError() << std::endl;
		return ;
	}
	if (!(soundtrack = Mix_LoadWAV("../music/towerfall.wav")))
	{
		std::cerr << "Error playing soundtrack: " << Mix_GetError() << std::endl;
		return ; 
	}
	Mix_FadeInChannel(-1, soundtrack, -1, 500);

}

bool			Graphics::isOpen(void) const
{
	return (_window ? true : false);
}

key				Graphics::keyPress(void)
{
	return (key::NO); // TODO
}

void			Graphics::draw(void)
{
}

void			Graphics::loop(SDL_Window * win)
{
	SDL_Event	currentEvent;

	while (win)
	{
		while (SDL_PollEvent(&currentEvent))
		{
			SDL_UpdateWindowSurface(win);
			SDL_PumpEvents();
			if (currentEvent.type == SDL_WINDOWEVENT && currentEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				SDL_DestroyWindow(win);
				win = NULL;
			}
		}
	}
}

SDL_Surface		*Graphics::drawImage(char * const path, SDL_Window * win)
{
	SDL_Surface	*loadedSurface = NULL;
	SDL_Surface	*finalSurface = NULL;
	
	int imgFlags = IMG_INIT_PNG;
    if( !(IMG_Init(imgFlags) & imgFlags ))
	{
		std::cerr << "SDL_Image init fail: " << IMG_GetError() << std::endl;
		return (NULL);
	}
    else
	{
		std::cout << "SDL_Image init successful" << std::endl;
		if (!(loadedSurface = IMG_Load(path)))
		{
			std::cerr << "SDL failed loading image: " << IMG_GetError() << std::endl;
			return (NULL);
		}
		else
		{
			std::cout << "SDL loaded image succesfully" << std::endl;
			finalSurface = SDL_ConvertSurface(loadedSurface, SDL_GetWindowSurface(win)->format, 0);
			if (!finalSurface)
			{
				std::cerr << "SDL failed transferring image to surface: " << IMG_GetError() << std::endl;
				return (NULL);
			}
			else
				std::cout << "SDL image succesfully transferred to new surface" << std::endl;
			SDL_FreeSurface(loadedSurface);
		}
		return (finalSurface);
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