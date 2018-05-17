#include <iostream>
#include <dlfcn.h>
#include "../inc/Api.class.hpp"
#include "../inc/lib.namespace.hpp"

int main(int ac, char **av)
{
	try
	{
		std::string		opt(manageOpt::getOpt(ac, av));
		std::string		lib(manageOpt::getPathLib(opt));

		void		*lol;
		Api		*(*mdr)();

		std::cout << lib.c_str() << std::endl;
		lol = dlopen(lib.c_str(), RTLD_NOW);
		if (!lol)
			std::cerr << dlerror() << std::endl;
		mdr = (Api *(*)())dlsym(lol, "create");
		if (!mdr)
			std::cerr << dlerror() << std::endl;
		Api		*ptdr = mdr();
		ptdr->openWindow(WIDTH_WINDOW, HEIGHT_WINDOW);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
    return 0;
}
