#include <iostream>
#include <dlfcn.h>

#include "../inc/Api.class.hpp"

int main()
{
	void		*lol;
	test		*(*mdr)();

	lol = dlopen("sfml_lib/sfml.so", RTLD_NOW);
	if (!lol)
		std::cerr << dlerror() << std::endl;
	mdr = (test *(*)())dlsym(lol, "create");
	if (!mdr)
		std::cerr << dlerror() << std::endl;
	test		*ptdr = mdr();
	ptdr->openWindow(800, 600);
    return 0;
}
