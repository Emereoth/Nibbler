#ifndef ITEST_HPP
# define ITEST_HPP

#include <stdio.h>

# define WIDTH_WINDOW 1920
# define HEIGHT_WINDOW 1080
# define SIZE_SQUARE (HEIGHT_WINDOW > WIDTH_WINDOW ? WIDTH_WINDOW / 50 : HEIGHT_WINDOW / 50)

enum KEY
{
	NO,
	LEFT,
	RIGHT
};

class Api {

	public:

		virtual void		run(size_t w, size_t h) = 0;
};

#endif