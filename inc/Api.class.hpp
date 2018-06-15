#ifndef API_HPP
# define API_HPP

#include <stdio.h>
#include "Map.class.hpp"
#include <cstdlib>

enum class key
{
	ONE,
	TWO,
	THREE,
	ESCAPE,
	NO,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum libName
{
	SFML,
	SDL,
	OPENGL
};

class AGraphics {

	public:

		virtual void			openWindow(void) = 0;
		virtual bool			isOpen(void) const = 0;
		virtual key				keyPress(void) = 0;
		virtual void			draw(Map &map) = 0;
		virtual void			closeWindow(void) = 0;
		virtual void			changeMusic(void) = 0;
		virtual std::string		getPathNibbler() = 0;

		size_t					_height;
		size_t					_width;
		float					_squareSize;
		int						name;
};

#endif