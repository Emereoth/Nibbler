/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:54 by acottier          #+#    #+#             */
/*   Updated: 2018/06/13 15:58:24 by acottier         ###   ########.fr       */
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
	_surfaceMap = 
	{
		{ sprite::HEAD_UP , loadSurface("texture/headUp.png", _window) } ,
		{ sprite::HEAD_DOWN , loadSurface("texture/headDown.png", _window) } ,
		{ sprite::HEAD_LEFT , loadSurface("texture/headLeft.png", _window) } ,
		{ sprite::HEAD_RIGHT , loadSurface("texture/headRight.png", _window) } ,
		{ sprite::BODY_H , loadSurface("texture/bodyH.png", _window) } ,
		{ sprite::BODY_V , loadSurface("texture/bodyV.png", _window) } ,
		{ sprite::TAIL_UP , loadSurface("texture/tailUp.png", _window) } ,
		{ sprite::TAIL_DOWN , loadSurface("texture/tailDown.png", _window) } ,
		{ sprite::TAIL_LEFT , loadSurface("texture/tailLeft.png", _window) } ,
		{ sprite::TAIL_RIGHT , loadSurface("texture/tailRight.png", _window) } ,
		{ sprite::BODY_UP_LEFT , loadSurface("texture/bodyUpLeft.png", _window) } ,
		{ sprite::BODY_UP_RIGHT , loadSurface("texture/bodyUpRight.png", _window) } ,
		{ sprite::BODY_DOWN_LEFT , loadSurface("texture/bodyDownLeft.png", _window) } ,
		{ sprite::BODY_DOWN_RIGHT , loadSurface("texture/bodydownRight.png", _window) } ,
		{ sprite::WALL , loadSurface("texture/wall.png", _window) } ,
		{ sprite::FOOD , loadSurface("texture/apple.png", _window) }
	};
	setMusic();
}

void			Graphics::setMusic()
{
	initAudio();
	_soundtrack = createAudio(MUSIC_PATH, 1, 64);
	playSoundFromMemory(_soundtrack, 64);
}

void			Graphics::changeMusic()
{
	freeAudio(_soundtrack);
	_soundtrack = createAudio(MUSIC_HARDCORE_PATH, 1, 64);
	playMusicFromMemory(_soundtrack, 64);
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
			float			widthPos = spaceAroundX + i % 62 * _squareSize;
			float			heightPos = spaceAroundY + i / 62 * _squareSize;
			dst.w = _squareSize;
			dst.h = _squareSize;
			dst.x = widthPos - 1;
			dst.y = heightPos - 1;
			if (SDL_BlitScaled(_surfaceMap[map.map[i]], NULL, SDL_GetWindowSurface(_window), &dst)!= 0)
			{
				closeWindow();
				throw SDL_BlitTransferFail();
			}
		}
	}
	SDL_UpdateWindowSurface(_window);
}

SDL_Surface		*Graphics::loadSurface(const char *texturePath, SDL_Window * win)
{
	SDL_Surface	*finalSurface = NULL;
	SDL_Surface	*img_load = IMG_Load(texturePath);


	if (img_load == NULL)
	{
		closeWindow();
		throw IMG_SurfaceLoadingFail();
	}
	finalSurface = SDL_ConvertSurface(img_load, SDL_GetWindowSurface(win)->format, 0);
	if (!finalSurface)
	{
		closeWindow();
		throw IMG_SurfaceConvertingFail();
	}
	return (finalSurface);
}

Graphics::Graphics(size_t width, size_t height, float squareSize)
{
	name = libName::SDL;
	_height = height;
	_width = width;
	_squareSize = squareSize;
}

void		Graphics::closeWindow(void)
{
	freeAudio(_soundtrack);
	endAudio();
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