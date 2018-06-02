/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:54 by acottier          #+#    #+#             */
/*   Updated: 2018/06/01 16:42:05 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libSDL.hpp"
#include <iostream>

#define MUSIC_PATH "music/towerfall2.wav"
#define MUSIC_HARDCORE_PATH "music/towerfall.wav"

void			Graphics::openWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || ! ( IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) )
	{
		closeWindow();
		throw SDL_InitFail();
	}
	if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) )
	{
		closeWindow();
		throw IMG_InitFail();
	}
	_window = SDL_CreateWindow("Nibbler (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_MOUSE_FOCUS);
	setMusic();
}

void			Graphics::setMusic()
{
	// initAudio();
	// _soundtrack = createAudio(MUSIC_PATH, 1, 64);
	// playMusicFromMemory(_soundtrack, 64);
	// SDL_Delay(5000);
	// // SDL_Delay(3000);
	// freeAudio(_soundtrack);
	// _soundtrack = createAudio(MUSIC_HARDCORE_PATH, 1, 64);
	// playMusicFromMemory(_soundtrack, 64);
}

bool			Graphics::isOpen(void) const
{
	return (_window ? true : false);
}

key				Graphics::keyPress(void)
{
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

	SDL_PumpEvents();
	while (SDL_PollEvent(&currentEvent))
	{
		if (SDL_KEYDOWN && eventMap.find(currentEvent.key.keysym.sym) != eventMap.end())
			return (eventMap[currentEvent.key.keysym.sym]);
		else if (currentEvent.type == SDL_WINDOWEVENT && currentEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			return (key::ESCAPE);
	}
	return (key::NO);
}

void			Graphics::draw(Map &map)
{
	SDL_Rect		dst;
	size_t			size = 62 * 62;
	float			spaceAroundX = (_width / 2) - (_squareSize * 31);
	float			spaceAroundY = (_height / 2) - (_squareSize * 31);
	
	SDL_FillRect(SDL_GetWindowSurface(_window), NULL, 0x0000000);
	for (size_t i = 0 ; i < size ; i++)
	{
		if (map.map[i] != sprite::SOIL)
		{
			SDL_Surface		*tmpSurface = loadSurface(map.map[i], _window);
			float			widthPos = spaceAroundX + i % 62 * _squareSize;
			float			heightPos = spaceAroundY + i / 62 * _squareSize;
			dst.w = _squareSize;
			dst.h = _squareSize;
			dst.x = widthPos;
			dst.y = heightPos;
			if (SDL_BlitScaled(tmpSurface, NULL, SDL_GetWindowSurface(_window), &dst)!= 0)
			{
				closeWindow();
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

SDL_Surface		*Graphics::loadSurface(sprite texture, SDL_Window * win)
{
	SDL_Surface	*finalSurface = NULL;

	if (_surfaceMap[texture] == NULL)
	{
		closeWindow();
		throw IMG_SurfaceLoadingFail();
	}
	finalSurface = SDL_ConvertSurface(_surfaceMap[texture], SDL_GetWindowSurface(win)->format, 0);
	if (!finalSurface)
	{
		closeWindow();
		throw IMG_SurfaceConvertingFail();
	}
	return (finalSurface);
}

Graphics::Graphics(size_t width, size_t height, float squareSize) : name(libName::SDL)
{
	_surfaceMap = 
	{
		{ sprite::HEAD_UP , IMG_Load("texture/headUp.png") } ,
		{ sprite::HEAD_DOWN , IMG_Load("texture/headDown.png") } ,
		{ sprite::HEAD_LEFT , IMG_Load("texture/headLeft.png") } ,
		{ sprite::HEAD_RIGHT , IMG_Load("texture/headRight.png") } ,
		{ sprite::BODY_H , IMG_Load("texture/bodyH.png") } ,
		{ sprite::BODY_V , IMG_Load("texture/bodyV.png") } ,
		{ sprite::TAIL_UP , IMG_Load("texture/tailUp.png") } ,
		{ sprite::TAIL_DOWN , IMG_Load("texture/tailDown.png") } ,
		{ sprite::TAIL_LEFT , IMG_Load("texture/tailLeft.png") } ,
		{ sprite::TAIL_RIGHT , IMG_Load("texture/tailRight.png") } ,
		{ sprite::BODY_UP_LEFT , IMG_Load("texture/bodyUpLeft.png") } ,
		{ sprite::BODY_UP_RIGHT , IMG_Load("texture/bodyUpRight.png") } ,
		{ sprite::BODY_DOWN_LEFT , IMG_Load("texture/bodyDownLeft.png") } ,
		{ sprite::BODY_DOWN_RIGHT , IMG_Load("texture/bodydownRight.png") } ,
		{ sprite::WALL , IMG_Load("texture/wall.png") } ,
		{ sprite::FOOD , IMG_Load("texture/apple.png") }
	};
	_height = height;
	_width = width;
	_squareSize = squareSize;
}

void		Graphics::closeWindow(void)
{
	SDL_DestroyWindow(_window);
	_window = NULL;
	for (std::map<sprite, SDL_Surface *>::iterator ii = _surfaceMap.begin() ; ii != _surfaceMap.end() ; ii++)
		delete ii->second;
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