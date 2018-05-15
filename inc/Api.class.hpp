#ifndef ITEST_HPP
# define ITEST_HPP

#include <stdio.h>

class Api {

	public:

		virtual void		openWindow(size_t w, size_t h) = 0;
};

#endif