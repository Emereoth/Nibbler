/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libOpenGL.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:34:38 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/15 13:32:51 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBOPENGL_HPP
# define LIBOPENGL_HPP

# include <GLFW/glfw3.h>
# include "../../inc/Api.class.hpp"

class Graphics : public Api {

	public:

		Graphics(void);
		virtual ~Graphics(void);

		void				openWindow(size_t w, size_t h);

};

extern "C" {
	Graphics				*create(void);
	void					del(Graphics *entry);
}

#endif