/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:55 by acottier          #+#    #+#             */
/*   Updated: 2018/05/16 19:07:55 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSDL_HPP
# define LIBSDL_HPP

#include "../SDL/include/SDL.h"
#include "../../inc/Api.class.hpp"

class Graphics : public Api
{
	public:
	
		SDL_Window	*window;
		Graphics(void);
		virtual ~Graphics(void);

		void		openWindow(size_t w, size_t h);
};

extern "C"
{
	Graphics		*create(void);
	void			del(Graphics *lol);
}
#endif