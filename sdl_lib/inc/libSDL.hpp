/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:55 by acottier          #+#    #+#             */
/*   Updated: 2018/05/22 17:05:37 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSDL_HPP
# define LIBSDL_HPP

#include <string>
#include "../SDL/include/SDL.h"
#include "../SDL_Image/SDL_image.h"
#include "../SDL_Mixer/SDL_mixer.h"
#include "../../inc/Api.class.hpp"

class Graphics : public Api
{
	public:
	
		explicit Graphics(void);
		virtual ~Graphics(void);

		void		openWindow(size_t w, size_t h) override;
		SDL_Surface	*drawImage(char * const path, SDL_Window * win);
		bool		isOpen(void) const override;
		key			keyPress(void) override;
		void		draw(void) override;
		void		setMusic();
		void		loop(SDL_Window * win /* TOO : ADD SAVE DATA STRUCTURE*/);
		
		libName		name;

	private:

		Graphics		&operator=(Graphics const & rhs) = delete;
		Graphics(Graphics const &) = default;
		
		SDL_Window	*_window;

};

extern "C"
{
	Graphics		*create(void);
	void			del(Graphics *lol);
}
#endif