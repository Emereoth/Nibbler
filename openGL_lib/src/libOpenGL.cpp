/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:26:49 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/17 11:48:00 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libOpenGL.hpp"
#include <iostream>

Graphics::Graphics(void)
{
	
}

void				Graphics::openWindow(size_t w, size_t h)
{
	if (!glfwInit())
	{
	    std::cerr << "Failed to initialize GLEW\n" << std::endl;
		return ;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window; // (Dans le code source qui accompagne, cette variable est globale)
	window = glfwCreateWindow( w, h, "Nibbler (OpenGL)", NULL, NULL);
	if (window == NULL)
	{
    	std::cerr << "Failed to open GLFW window." << std::endl;
    	glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window);
	// glewExperimental = true; // Nécessaire dans le profil de base
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n" << std::endl;
		return ;
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	if (present)
	{
		const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		std::cout << "name joystick => " << name << std::endl;
	}
	while(glfwWindowShouldClose(window) == 0 )
	{
    	glfwSwapBuffers(window);
    	glfwWaitEvents();
		int state = glfwGetKey(window, GLFW_KEY_DOWN);
		if (state == GLFW_PRESS)
			std::cout << "key press" << std::endl;
	}
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