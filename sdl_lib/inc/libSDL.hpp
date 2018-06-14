/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libSDL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:53:55 by acottier          #+#    #+#             */
/*   Updated: 2018/06/14 16:35:00 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSDL_HPP
# define LIBSDL_HPP

#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
// #include <audio.hpp>
#include <sstream>
#include "../../inc/Api.class.hpp"

class Graphics : public AGraphics
{
	public:
	
		explicit Graphics(size_t width, size_t height, float squareSize);
		virtual ~Graphics(void);

		void		openWindow(void) override;
		bool		isOpen(void) const override;
		key			keyPress(void) override;
		void		draw(Map &map) override;
		void		closeWindow(void) override;
		void		changeMusic(void) override;
		
		class SDL_WindowFail : public std::exception
		{
			public:
			virtual const char *what() const throw()
			{
				std::ostringstream	stream;
				stream << "SDL couldn't create window " << SDL_GetError();
				return (stream.str().c_str());
			}
		};

		class SDL_InitFail : public std::exception
		{
			public:
			virtual const char *what() const throw()
			{
				std::ostringstream	stream;
				stream << "SDL initialization error: " << SDL_GetError();
				return (stream.str().c_str());
			}
		};

		class IMG_InitFail : public std::exception
		{
			public:
			virtual const char *what() const throw()
			{
				std::ostringstream	stream;
				stream << "SDL_Image initialization error: " << IMG_GetError();
				return (stream.str().c_str());
			}
		};
		
		class SDL_BlitTransferFail : public std::exception
		{
			public:
			virtual const char *what() const throw()
			{
				std::ostringstream	stream;
				stream << "SDL bit transfer error: " << SDL_GetError();
				return (stream.str().c_str());
			}
		};

		class IMG_SurfaceLoadingFail : public std::exception
		{
			public:
			virtual const char *what() const throw()
			{
				std::ostringstream	stream;
				stream << "SDL image loading error: " << IMG_GetError();
				return (stream.str().c_str());
			}
		};

		class IMG_SurfaceConvertingFail : public std::exception
		{
			public:
			virtual const char *what() const throw()
			{
				std::ostringstream	stream;
				stream << "SDL surface converting error: " << IMG_GetError();
				return (stream.str().c_str());
			}
		};

	private:

		explicit Graphics(void);
		Graphics		&operator=(Graphics const & rhs) = delete;
		Graphics(Graphics const &) = default;

		SDL_Surface	*loadSurface(const char * texturePath, SDL_Window * win);
		void		setMusic(void);

		SDL_Window						*_window;
		std::map<sprite, SDL_Surface *>	_surfaceMap;
		Mix_Music						*_soundtrack;
};

extern "C"
{
	Graphics		*create(size_t width, size_t height, float squareSize);
	void			del(Graphics *lol);
}
#endif