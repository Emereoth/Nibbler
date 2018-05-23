/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:34:38 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/23 14:26:21 by acottier         ###   ########.fr       */
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

		Graphics(void);
		Graphics(Graphics const &src);
		virtual ~Graphics(void);

		Graphics			&operator=(Graphics const &rhs);

		void				openWindow(size_t w, size_t h);
		bool				isOpen(void) const;
		key					keyPress(void);
		void				draw(void);

		libName				name;

	private:

		GLFWwindow			*_window;

};

extern "C" {
	Graphics				*create(void);
	void					del(Graphics *entry);
}

#endif