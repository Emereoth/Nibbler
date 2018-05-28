/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:26:49 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/26 14:47:18 by acottier         ###   ########.fr       */
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
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(_width, _height, "Nibbler (OpenGL)", NULL, NULL);
	if (_window == NULL)
	{
    	std::cerr << "Failed to open GLFW _window." << std::endl;
    	glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(_window);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n" << std::endl;
		return ;
	}
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
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
	// GLuint texture;
	// GLenum internFormat(0);
	// GLenum format(0);
	// int width, height, bpp;

	// glGenTextures(1, &texture);                                        // Generation de l'iD
	// glBindTexture(GL_TEXTURE_2D,
	// 			  texture);                                // Verouillage, obligatoire pour modification du GLuint
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // Les textures proche sont lissées
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // Les textures éloignées sont lissées
	// texture = SOIL_load_OGL_texture(
	// 	"./texture/wall.png",
    //     SOIL_LOAD_RGB,
    //     SOIL_CREATE_NEW_ID,
    //     SOIL_FLAG_INVERT_Y
	// );
	// glTexImage2D(GL_TEXTURE_2D, 0, internFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	// glGenerateMipmap(GL_TEXTURE_2D);
	// stbi_image_free(data);                                                // Liberation memoire
	// glBindTexture(GL_TEXTURE_2D, 0);


	// //////////////////////////////////////////////
	// glBindTexture(GL_TEXTURE_2D, texture);
	// t_coordd start = {};
	// start.x = ((0 * 2.0) / _width) - 1.0;
	// start.y = ((0 * 2.0) / _height) - 1.0;

	// t_coordd end = {};
	// end.x = (((0 + _squareSize) * 2.0) / _width) - 1.0;
	// end.y = (((0 + _squareSize) * 2.0) / _height) - 1.0;

	// glBegin(GL_QUADS);
	// glTexCoord2d(0, 0);
	// glVertex2d(start.x, -end.y);    // bottom Left Corner
	// glTexCoord2d(0, 1);
	// glVertex2d(start.x, -start.y);    // upper Left Corner
	// glTexCoord2d(1, 1);
	// glVertex2d(end.x, -start.y);    // upper Right Corner
	// glTexCoord2d(1, 0);
	// glVertex2d(end.x, -end.y);        // bottom Right Corner
	// glEnd();
	// glBindTexture(GL_TEXTURE_2D, 0);
	// (void)map;
	// (void)bpp;
	// (void)width;
	// (void)height;
	// (void)format;
	// (void)internFormat;
	(void)map;
}

Graphics::~Graphics(void)
{
	return ;
}

Graphics			*create(size_t width, size_t height, float squareSize)
{
	return new Graphics(width, height, squareSize);
}

void				del(Graphics *entry)
{
	delete entry;
}