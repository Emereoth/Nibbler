/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:26:49 by rvievill          #+#    #+#             */
/*   Updated: 2018/06/13 19:22:12 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libOpenGL.hpp"
#include <iostream>

key						Graphics::keyUse = key::NO;

static void				keyCallback(GLFWwindow* window, int keyVal, int scancode, int action, int mods)
{
	static_cast<void>(scancode);
	static_cast<void>(window);
	static_cast<void>(mods);
	static std::map<int, key>		eventMap = {
		{GLFW_KEY_DOWN, key::DOWN},
		{GLFW_KEY_LEFT, key::LEFT},
		{GLFW_KEY_RIGHT, key::RIGHT},
		{GLFW_KEY_UP, key::UP},
		{GLFW_KEY_1, key::ONE},
		{GLFW_KEY_2, key::TWO},
		{GLFW_KEY_3, key::THREE},
		{GLFW_KEY_ESCAPE, key::ESCAPE},
		{GLFW_KEY_UNKNOWN, key::NO}
	};

	if (action == GLFW_PRESS)
	{
		if (eventMap.find(keyVal) == eventMap.end())
			Graphics::keyUse = key::NO;
		else
			Graphics::keyUse = eventMap[keyVal];
			
	}
}

Graphics::Graphics(size_t width, size_t height, float squareSize)
{
	name = OPENGL;
	_width = width;
	_height = height;
	_squareSize = squareSize;
}

Graphics::~Graphics(void)
{
	return ;
}

void				Graphics::setMusic()
{
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	_soundtrack = createAudio(MUSIC_PATH, 1, 64);
	playSoundFromMemory(_soundtrack, 64);
}

void			Graphics::changeMusic()
{
	endAudio();
	initAudio();
	freeAudio(_soundtrack);
	_soundtrack = createAudio(MUSIC_HARDCORE_PATH, 1, 64);
	playMusicFromMemory(_soundtrack, 64);
}

void				Graphics::openWindow(void)
{
	if (!glfwInit())
	{
	    std::cerr << "Failed to initialize GLEW\n" << std::endl;
		return ;
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	_window = glfwCreateWindow(_width, _height, "Nibbler (OpenGL)", NULL, NULL);
	if (_window == NULL)
	{
    	std::cerr << "Failed to open GLFW _window." << std::endl;
    	glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(_window);
	glfwSetKeyCallback(_window, keyCallback);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_texture[sprite::HEAD_UP] = loadTexture("texture/headUp.png");
	_texture[sprite::HEAD_DOWN] = loadTexture("texture/headDown.png");
	_texture[sprite::HEAD_LEFT] = loadTexture("texture/headLeft.png");
	_texture[sprite::HEAD_RIGHT] = loadTexture("texture/headRight.png");
	_texture[sprite::BODY_H] = loadTexture("texture/bodyH.png");
	_texture[sprite::BODY_V] = loadTexture("texture/bodyV.png");
	_texture[sprite::TAIL_UP] = loadTexture("texture/tailUp.png");
	_texture[sprite::TAIL_DOWN] = loadTexture("texture/tailDown.png");
	_texture[sprite::TAIL_LEFT] = loadTexture("texture/tailLeft.png");
	_texture[sprite::TAIL_RIGHT] = loadTexture("texture/tailRight.png");
	_texture[sprite::BODY_UP_LEFT] = loadTexture("texture/bodyUpLeft.png");
	_texture[sprite::BODY_UP_RIGHT] = loadTexture("texture/bodyUpRight.png");
	_texture[sprite::BODY_DOWN_LEFT] = loadTexture("texture/bodyDownLeft.png");
	_texture[sprite::BODY_DOWN_RIGHT] = loadTexture("texture/bodyDownRight.png");
	_texture[sprite::FOOD] = loadTexture("texture/apple.png");
	_texture[sprite::WALL] = loadTexture("texture/wall.png");
	setMusic();
}

bool				Graphics::isOpen(void) const
{
	return (_window ? true: false);
}

key					Graphics::keyPress(void)
{
	Graphics::keyUse = key::NO;
	glfwPollEvents();
	return (Graphics::keyUse);
}

void				Graphics::draw(Map &map)
{
	t_form			infoForm = {};

	glClear(GL_COLOR_BUFFER_BIT);
	infoForm.sizeY = 2.0f / 62.0f;
	infoForm.sizeX = _squareSize / (_width / 2);
	infoForm.posX = -(infoForm.sizeX * 31);
	infoForm.posY = 1;
	for (size_t i = 0; i < 62 * 62; i++)
	{
		if (i != 0 && i % map.offsetMap == 0)
		{
			infoForm.posY -= infoForm.sizeY;
			infoForm.posX = -(infoForm.sizeX * 31);
		}
		if (map.map[i] != sprite::SOIL)
			putTexture(map.map[i], infoForm);
		infoForm.posX += infoForm.sizeX;
	}
	glFlush();
	glfwSwapBuffers(_window);
 	(void)map;
}


void				Graphics::closeWindow(void)
{
	glfwTerminate();
	_window = NULL;
}

GLuint				Graphics::loadTexture(const char *texturePath)
{
	GLuint			tex;
	
    glGenTextures(1, &tex); 
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Les textures proche sont lissées
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	tex = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
	(
		texturePath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (tex);
}

void				Graphics::putTexture(sprite sprite, t_form &infoForm)
{
	glBindTexture(GL_TEXTURE_2D, _texture[sprite]);
	glBegin(GL_QUADS); // Start drawing a quad primitive
	glTexCoord2d(0, 0);
	glVertex2d(infoForm.posX, infoForm.posY - infoForm.sizeY); // The bottom left corner
	glTexCoord2d(0, 1);
	glVertex2d(infoForm.posX, infoForm.posY); // The upper left corner
	glTexCoord2d(1, 1);
	glVertex2d(infoForm.posX + infoForm.sizeX, infoForm.posY); // The upper right corner
	glTexCoord2d(1, 0);
	glVertex2d(infoForm.posX + infoForm.sizeX, infoForm.posY - infoForm.sizeY); // The bottom right corner
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

Graphics			*create(size_t width, size_t height, float squareSize)
{
	return new Graphics(width, height, squareSize);
}

void				del(Graphics *entry)
{
	delete entry;
}