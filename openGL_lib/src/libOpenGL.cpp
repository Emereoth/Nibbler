/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:26:49 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/31 13:53:14 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libOpenGL.hpp"
#include <iostream>

Graphics::Graphics(size_t width, size_t height, size_t squareSize) : name(libName::OPENGL)
{
	_width = width;
	_height = height;
	_squareSize = squareSize;
}

Graphics::~Graphics(void)
{
	return ;
}

void				Graphics::openWindow(void)
{
	if (!glfwInit())
	{
	    std::cerr << "Failed to initialize GLEW\n" << std::endl;
		return ;
	}
	_window = glfwCreateWindow(_width, _height, "Nibbler (OpenGL)", NULL, NULL);
	if (_window == NULL)
	{
    	std::cerr << "Failed to open GLFW _window." << std::endl;
    	glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(_window);
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
}

bool				Graphics::isOpen(void) const
{
	return (_window ? true: false);
}

key					Graphics::keyPress(void)
{
	glfwPollEvents();
	return (key::NO);
}

void				Graphics::draw(Map &map)
{
	t_form			infoForm = {};

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
		if (map.map[i] == 1)
			putTexture(sprite::WALL, infoForm);
		infoForm.posX += infoForm.sizeX;
	}
	glFlush();
	glfwSwapBuffers(_window);
 	(void)map;
}


void				Graphics::closeWindow(void)
{
	glfwDestroyWindow(_window);
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