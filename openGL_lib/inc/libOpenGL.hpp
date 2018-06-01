/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:34:38 by rvievill          #+#    #+#             */
/*   Updated: 2018/06/01 09:59:16 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBOPENGL_HPP
# define LIBOPENGL_HPP

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <SOIL2.h>
# include "../../inc/Api.class.hpp"
# include <map>

typedef struct		s_form
{
	double			posX;
	double			posY;
	double			sizeX;
	double			sizeY;
}					t_form;

class Graphics : public AGraphics {

	public:

		explicit Graphics(size_t width, size_t height, size_t squareSize);
		virtual ~Graphics(void);


		void				openWindow(void) override;
		bool				isOpen(void) const override;
		key					keyPress(void) override;
		void				draw(Map &map) override;
		void				closeWindow(void) override;

		libName				name;
		static key			keyUse;
		

	private:

		Graphics(void) = default;
		Graphics(Graphics const &src) = default;

		Graphics			&operator=(Graphics const &rhs) = default;

		GLuint				loadTexture(const char *texturePath);
		void				putTexture(sprite sprite, t_form &infoForm);

		GLFWwindow					*_window;
		std::map<sprite, GLuint>	_texture;


};

extern "C" {
	Graphics				*create(size_t width, size_t height, float squareSize);
	void					del(Graphics *entry);
}

#endif