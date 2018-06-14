/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:54 by acottier          #+#    #+#             */
/*   Updated: 2018/06/14 19:17:19 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libSDL.hpp"
#include <iostream>

#define MUSIC_PATH "music/towerfall.wav"
#define MUSIC_HARDCORE_PATH "music/towerfall_hard.wav"

void			Graphics::openWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || ! ( IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) )
		throw SDL_InitFail();
	if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) )
		throw IMG_InitFail();
	if ((_window = SDL_CreateWindow("Nibbler (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_MOUSE_FOCUS)) == NULL)
		throw SDL_WindowFail();
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

std::string				Graphics::getPathNibbler()
{
	std::string		pathApp(getwd(NULL));
	int				size = pathApp.find("nibbler") + 7;

	return (pathApp.substr(0, size) + "/");
}

void			Graphics::setMusic()
{
	std::string		music = _pathNibbler + MUSIC_PATH;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)== -1)
		throw std::runtime_error("Mix audio failed !");
	_soundtrack = Mix_LoadMUS(music.c_str());
	Mix_PlayMusic(_soundtrack, -1);
}

void			Graphics::changeMusic()
{
	std::string		music = _pathNibbler + MUSIC_HARDCORE_PATH;

	Mix_FreeMusic(_soundtrack);
	_soundtrack = Mix_LoadMUS(music.c_str());
	Mix_PlayMusic(_soundtrack, -1);
}

bool			Graphics::isOpen(void) const
{
	return (_window ? true : false);
}

key				Graphics::keyPress(void)
{
	SDL_Event		currentEvent;
	key				res = key::NO;
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
		if (res == key::NO && SDL_KEYDOWN && eventMap.find(currentEvent.key.keysym.sym) != eventMap.end())
			res = eventMap[currentEvent.key.keysym.sym];
		else if (res == key::NO && currentEvent.type == SDL_WINDOWEVENT && currentEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			res = key::ESCAPE;
	}
	return (res);
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
			dst.w = _squareSize + 1;
			dst.h = _squareSize + 1;
			dst.x = widthPos;
			dst.y = heightPos;
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
	std::string	tex = _pathNibbler + texturePath;
	SDL_Surface	*finalSurface = NULL;
	SDL_Surface	*img_load = IMG_Load(tex.c_str());


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
	_pathNibbler = getPathNibbler();
}

void		Graphics::closeWindow(void)
{
	Mix_FreeMusic(_soundtrack);
	Mix_CloseAudio();
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