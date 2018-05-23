/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:34:38 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/23 16:45:24 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBOPENGL_HPP
# define LIBOPENGL_HPP

# include <GL/glew.h>
# include <GLFW/glfw3.h>
#include <SOIL2.h>
# include "../../inc/Api.class.hpp"

class Graphics : public AGraphics {

	public:

		explicit Graphics(size_t width, size_t height, size_t squareSize);
		virtual ~Graphics(void);


		void				openWindow(void) override;
		bool				isOpen(void) const override;
		key					keyPress(void) override;
		void				draw(Map map) override;

		libName				name;

	private:

		Graphics(void) = default;
		Graphics(Graphics const &src) = default;
		Graphics			&operator=(Graphics const &rhs) = default;

		GLFWwindow			*_window;

};

extern "C" {
	Graphics				*create(size_t width, size_t height, size_t squareSize);
	void					del(Graphics *entry);
}

#endif