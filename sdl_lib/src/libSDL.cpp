/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:54 by acottier          #+#    #+#             */
/*   Updated: 2018/05/23 17:35:43 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libSDL.hpp"
#include <iostream>

void			Graphics::openWindow()
{
	SDL_Window	*win;
	SDL_Surface	*newSurface = NULL;
	SDL_Rect	dst;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDL init error :" << SDL_GetError() << std::endl;
		return ;
	}
	win = SDL_CreateWindow("Nibbler (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_MOUSE_FOCUS);
	newSurface = drawImage((char *)"../texture/headUp.png", win);
	dst.x = 0;
	dst.y = 0;
	dst.w = SIZE_SQUARE;
	dst.h = SIZE_SQUARE;
	if (SDL_BlitScaled(newSurface, NULL, SDL_GetWindowSurface(win), &dst)!= 0)
		std::cerr << "SDL blit transfer error: " << SDL_GetError() << std::endl;
	setMusic();
}

void			Graphics::setMusic() const
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
	key				res;
	SDL_Event		currentEvent;
	std::map<SDL_Keycode, key>	eventMap =
	{
		{SDLK_ESCAPE, key::ESCAPE},
		{SDLK_LEFT, key::LEFT},
		{SDLK_RIGHT, key::RIGHT},
		{SDLK_UP, key::UP},
		{SDLK_DOWN, key::DOWN},
		{SDLK_1, key::ONE},
		{SDLK_2, key::TWO},
		{SDLK_3, key::THREE}
	};
	
	SDL_PollEvent(&currentEvent);
	res = key::NO;
	if (SDL_KEYDOWN && eventMap.find(currentEvent.key.keysym.sym) != eventMap.end())
		res = eventMap[currentEvent.key.keysym.sym];
	// TODO :: PURGE EVENT QUEUE
	return (res);
}

void			Graphics::draw(Map map)
{
	(void)map;
}

// void			Graphics::loop(SDL_Window * win)
// {
// 	SDL_Event	currentEvent;

// 	while (win)
// 	{
// 		while (SDL_PollEvent(&currentEvent))
// 		{
// 			SDL_UpdateWindowSurface(win);
// 			SDL_PumpEvents();
// 			if (currentEvent.type == SDL_WINDOWEVENT && currentEvent.window.event == SDL_WINDOWEVENT_CLOSE)
// 			{
// 				SDL_DestroyWindow(win);
// 				win = NULL;
// 			}
// 		}
// 	}
// }

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

Graphics::Graphics(size_t height, size_t width, size_t squareSize) : name(libName::SDL)
{
	int imgFlags = IMG_INIT_PNG;
	
	if( !(IMG_Init(imgFlags) & imgFlags ))
	{
		std::cerr << "SDL_Image init fail: " << IMG_GetError() << std::endl;
		return ;
	}
	_surfaceMap = 
	{
		{ sprite::HEAD_UP , IMG_Load("../texture/headUp.png") } ,
		{ sprite::HEAD_DOWN , IMG_Load("../texture/headDown.png") } ,
		{ sprite::HEAD_LEFT , IMG_Load("../texture/headLeft.png") } ,
		{ sprite::HEAD_RIGHT , IMG_Load("../texture/headRight.png") } ,
		{ sprite::BODY_H , IMG_Load("../texture/bodyH.png") } ,
		{ sprite::BODY_V , IMG_Load("../texture/bodyV.png") } ,
		{ sprite::TAIL_UP , IMG_Load("../texture/tailUp.png") } ,
		{ sprite::TAIL_DOWN , IMG_Load("../texture/tailDown.png") } ,
		{ sprite::TAIL_LEFT , IMG_Load("../texture/tailLeft.png") } ,
		{ sprite::TAIL_RIGHT , IMG_Load("../texture/tailRight.png") } ,
		{ sprite::BODY_UP_LEFT , IMG_Load("../texture/bodyUpLeft.png") } ,
		{ sprite::BODY_UP_RIGHT , IMG_Load("../texture/bodyUpRight.png") } ,
		{ sprite::BODY_DOWN_LEFT , IMG_Load("../texture/bodyDownLeft.png") } ,
		{ sprite::BODY_DOWN_RIGHT , IMG_Load("../texture/bodydownRight.png") } ,
		{ sprite::WALL , IMG_Load("../texture/wall.png") } ,
		{ sprite::FOOD , IMG_Load("../texture/food.png") }
	};
	_height = height;
	_width = width;
	_squareSize = squareSize;
}

Graphics::Graphics(void)
{
}

Graphics::~Graphics(void)
{
}

Graphics			*create(size_t height, size_t width, size_t squareSize)
{
	return new Graphics(height, width, squareSize);
}

void				del(Graphics *test)
{
	delete test;
}