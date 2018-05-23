#ifndef ITEST_HPP
# define ITEST_HPP

#include <stdio.h>
#include "Map.class.hpp"

# define WIDTH_WINDOW 1920
# define HEIGHT_WINDOW 1080
# define SIZE_SQUARE (HEIGHT_WINDOW > WIDTH_WINDOW ? WIDTH_WINDOW / 50 : HEIGHT_WINDOW / 50)

enum class	key
{
	NO,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ONE,
	TWO,
	THREE,
	ESCAPE
};

enum class	sprite
{
	HEAD_UP,
	HEAD_DOWN,
	HEAD_LEFT,
	HEAD_RIGHT,
	BODY_H,
	BODY_V,
	TAIL_UP,
	TAIL_DOWN,
	TAIL_LEFT,
	TAIL_RIGHT,
	BODY_UP_LEFT,
	BODY_UP_RIGHT,
	BODY_DOWN_LEFT,
	BODY_DOWN_RIGHT,
	WALL,
	FOOD
};

enum class	libName
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
		virtual void			draw(Map map) = 0;

	protected:
		
		size_t					_height;
		size_t					_width;
		size_t					_squareSize;

};

#endif