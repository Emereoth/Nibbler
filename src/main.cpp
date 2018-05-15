#include <iostream>
#include <dlfcn.h>

#include "../inc/Api.class.hpp"

int main()
{
	void		*lol;
	Api		*(*mdr)();

	lol = dlopen("sfml_lib/sfml.so", RTLD_NOW);
	if (!lol)
		std::cerr << dlerror() << std::endl;
	mdr = (Api *(*)())dlsym(lol, "create");
	if (!mdr)
		std::cerr << dlerror() << std::endl;
	Api		*ptdr = mdr();
	ptdr->openWindow(1920, 1080);
    return 0;
}
