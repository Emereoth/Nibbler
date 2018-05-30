/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:26:49 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/30 17:17:58 by rvievill         ###   ########.fr       */
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
	GLuint			texture;
	auto sizeY = _squareSize / (_height / 2);
	auto sizeX = _squareSize / (_width / 2);
	auto startX = -(sizeX * 31);
	auto startY = 1;

    glGenTextures(1, &texture); 
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Les textures proche sont lissées
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
	(
		"texture/wall.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glColor3f(255,255,255);
	glBegin(GL_QUADS); // Start drawing a quad primitive
	glTexCoord2d(0, 0);
	glVertex2d(startX, startY - sizeY); // The bottom left corner
	glTexCoord2d(0, 1);
	glVertex2d(startX, startY); // The upper left corner
	glTexCoord2d(1, 1);
	glVertex2d(startX + sizeX, startY); // The upper right corner
	glTexCoord2d(1, 0);
	glVertex2d(startX + sizeX, startY - sizeY); // The bottom right corner
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glFlush();
	glfwSwapBuffers(_window);
 	(void)map;
}

Graphics::~Graphics(void)
{
	return ;
}

void				Graphics::closeWindow(void)
{
	glfwDestroyWindow(_window);
}

Graphics			*create(size_t width, size_t height, float squareSize)
{
	return new Graphics(width, height, squareSize);
}

void				del(Graphics *entry)
{
	delete entry;
}