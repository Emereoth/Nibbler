#ifndef ITEST_HPP
# define ITEST_HPP

#include <stdio.h>

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
	THREE
};

enum class	libName
{
	SFML,
	SDL,
	OPENGL
};

class Api {

	public:

		virtual void			openWindow(size_t w, size_t h) = 0;
		virtual bool			isOpen(void) const = 0;
		virtual key				keyPress(void) = 0;
		virtual void			draw(void) = 0;
};

#endif