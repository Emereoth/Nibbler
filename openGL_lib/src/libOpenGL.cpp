/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:26:49 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/16 15:41:40 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libOpenGL.hpp"
#include <iostream>

Graphics::Graphics(void)
{
	
}

void				Graphics::openWindow(size_t w, size_t h)
{
	if (!glfwInit()) {
	    std::cerr << "Failed to initialize GLEW\n" << std::endl;
		return ;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window; // (Dans le code source qui accompagne, cette variable est globale)
	window = glfwCreateWindow( w, h, "Nibbler", NULL, NULL);
	if (window == NULL)
	{
    	std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" << std::endl;
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

	while(glfwWindowShouldClose(window) == 0 )
	{
    	glfwSwapBuffers(window);
    	glfwPollEvents();
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