/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:54 by acottier          #+#    #+#             */
/*   Updated: 2018/05/29 15:24:34 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libSDL.hpp"
#include <iostream>

void			Graphics::openWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || ! ( IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) )
		throw SDL_InitFail();
	if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) )
		throw IMG_InitFail();
	_window = SDL_CreateWindow("Nibbler (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_MOUSE_FOCUS);
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

void			Graphics::draw(Map &map)
{
	SDL_Rect		dst;
	float			spaceAroundX = (_width / 2) - (_squareSize * 31);
	
	for (size_t y = 0 ; y < 62 ; y++)
	{
		for (size_t x = 0 ; x < 62 ; x++)
		{
			if (map.map[y][x] == '1')
			{
				SDL_Surface		*tmpSurface = loadSurface(_surfaceMap[sprite::WALL], _window);
				float			width = spaceAroundX + (x * _squareSize);
				float			height = y * _squareSize;

				dst.w = SIZE_SQUARE;
				dst.h = SIZE_SQUARE;
				dst.x = width;
				dst.y = height;
				if (SDL_BlitScaled(tmpSurface, NULL, SDL_GetWindowSurface(_window), &dst)!= 0)
					throw SDL_BlitTransferFail();
			}
		}
	}
	SDL_UpdateWindowSurface(_window);
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

SDL_Surface		*Graphics::loadSurface(std::string path, SDL_Window * win)
{
	SDL_Surface	*finalSurface = NULL;
	SDL_Surface	*tmpSurface = NULL;

	tmpSurface = IMG_Load(path.c_str());
	if (!tmpSurface)
		throw IMG_SurfaceLoadingFail();
	finalSurface = SDL_ConvertSurface(tmpSurface, SDL_GetWindowSurface(win)->format, 0);
	if (!finalSurface)
		throw IMG_SurfaceConvertingFail();
	SDL_FreeSurface(tmpSurface);
	return (finalSurface);
}

Graphics::Graphics(size_t width, size_t height, float squareSize) : name(libName::SDL)
{
	_surfaceMap = 
	{
		{ sprite::HEAD_UP , "texture/headUp.png" } ,
		{ sprite::HEAD_DOWN , "texture/headDown.png" } ,
		{ sprite::HEAD_LEFT , "texture/headLeft.png" } ,
		{ sprite::HEAD_RIGHT , "texture/headRight.png" } ,
		{ sprite::BODY_H , "texture/bodyH.png" } ,
		{ sprite::BODY_V , "texture/bodyV.png" } ,
		{ sprite::TAIL_UP , "texture/tailUp.png" } ,
		{ sprite::TAIL_DOWN , "texture/tailDown.png" } ,
		{ sprite::TAIL_LEFT , "texture/tailLeft.png" } ,
		{ sprite::TAIL_RIGHT , "texture/tailRight.png" } ,
		{ sprite::BODY_UP_LEFT , "texture/bodyUpLeft.png" } ,
		{ sprite::BODY_UP_RIGHT , "texture/bodyUpRight.png" } ,
		{ sprite::BODY_DOWN_LEFT , "texture/bodyDownLeft.png" } ,
		{ sprite::BODY_DOWN_RIGHT , "texture/bodydownRight.png" } ,
		{ sprite::WALL , "texture/wall.png" } ,
		{ sprite::FOOD , "texture/apple.png" }
	};
	_height = height;
	_width = width;
	_squareSize = squareSize;
}

void		Graphics::closeWindow(void)
{
	SDL_DestroyWindow(_window);
	_window = NULL;
}

Graphics::Graphics(void)
{
}

Graphics::~Graphics(void)
{
}

Graphics			*create(size_t width, size_t height, float squareSize)
{
	return new Graphics(width, height, squareSize);
}

void				del(Graphics *test)
{
	delete test;
}