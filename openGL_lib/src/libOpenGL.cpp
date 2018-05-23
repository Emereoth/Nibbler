/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:26:49 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/22 17:13:08 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libOpenGL.hpp"
#include <iostream>

Graphics::Graphics(void) : name(libName::OPENGL)
{
	
}

void				Graphics::openWindow(size_t w, size_t h)
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
	_window = glfwCreateWindow( w, h, "Nibbler (OpenGL)", NULL, NULL);
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
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	if (present)
	{
		const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		std::cout << "name joystick => " << name << std::endl;
	}
}

bool				Graphics::isOpen(void) const
{
	return (_window ? true: false);
}

key					Graphics::keyPress(void)
{
	return (key::NO);
}

void				Graphics::draw(void)
{

}

Graphics::~Graphics(void)
{
	return ;
}

Graphics			*create(void)
{
	return new Graphics;
}

void				del(Graphics *entry)
{
	delete entry;
}