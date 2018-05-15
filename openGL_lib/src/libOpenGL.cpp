/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:26:49 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/15 13:35:01 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libOpenGL.hpp"
#include <iostream>

Graphics::Graphics(void)
{
	
}

void				Graphics::openWindow(size_t w, size_t h)
{
	(void)w;
	(void)h;
	if (!glfwInit())
	{
		std::cerr << "fail" << std::endl;
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