/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:34:38 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/17 17:12:31 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBOPENGL_HPP
# define LIBOPENGL_HPP

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "../../inc/Api.class.hpp"

class Graphics : public Api {

	public:

		Graphics(void);
		virtual ~Graphics(void);

		void				run(size_t w, size_t h);

};

extern "C" {
	Graphics				*create(void);
	void					del(Graphics *entry);
}

#endif