#ifndef ITEST_HPP
# define ITEST_HPP

#include <stdio.h>

# define WIDTH_WINDOW 1920
# define HEIGHT_WINDOW 1080

class Api {

	public:

		virtual void		run(size_t w, size_t h) = 0;
};

#endif