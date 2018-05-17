/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:55 by acottier          #+#    #+#             */
/*   Updated: 2018/05/17 18:32:31 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSDL_HPP
# define LIBSDL_HPP

#include <string.h>
#include "../SDL/include/SDL.h"
#include "../SDL_Image/SDL_image.h"
#include "../../inc/Api.class.hpp"

class Graphics : public Api
{
	public:
	
		SDL_Window	*window;
		Graphics(void);
		virtual ~Graphics(void);

		void		run(size_t w, size_t h);
		int			drawImage(std::string const & path, SDL_Window * win);

	private:

		Graphics		&operator=(Graphics const & rhs) = delete;
		Graphics(Graphics const &) = default;
};

extern "C"
{
	Graphics		*create(void);
	void			del(Graphics *lol);
}
#endif