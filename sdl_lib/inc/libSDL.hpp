/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:55 by acottier          #+#    #+#             */
/*   Updated: 2018/05/23 16:47:26 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSDL_HPP
# define LIBSDL_HPP

#include <string>
#include <map>
#include "../SDL/include/SDL.h"
#include "../SDL_Image/SDL_image.h"
#include "../SDL_Mixer/SDL_mixer.h"
#include "../../inc/Api.class.hpp"

class Graphics : public AGraphics
{
	public:
	
		explicit Graphics(size_t height, size_t width, size_t squareSize);
		virtual ~Graphics(void);

		void		openWindow(void) override;
		SDL_Surface	*drawImage(char * const path, SDL_Window * win);
		bool		isOpen(void) const override;
		key			keyPress(void) override;
		void		draw(Map map) override;
		void		setMusic(void) const;
		
		libName		name;

	private:

		explicit Graphics(void);
		Graphics		&operator=(Graphics const & rhs) = delete;
		Graphics(Graphics const &) = default;
		
		SDL_Window						*_window;
		std::map<sprite, SDL_Surface *>	_surfaceMap;
};

extern "C"
{
	Graphics		*create(void);
	void			del(Graphics *lol);
}
#endif