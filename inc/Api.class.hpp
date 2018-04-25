#ifndef ITEST_HPP
# define ITEST_HPP

#include <stdio.h>

class test {

	public:

		virtual void		openWindow(size_t w, size_t h) = 0;
};

#endif