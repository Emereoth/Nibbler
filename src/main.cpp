#include <iostream>
#include <dlfcn.h>
#include "../inc/Api.class.hpp"
#include "../inc/lib.namespace.hpp"
// #include "../inc/Map.class.hpp"
#include <fcntl.h>

int main(int ac, char **av)
{
	try
	{
		Map					test;
		unsigned int		seed;

		read(open("/dev/urandom", O_RDONLY), &seed, sizeof(seed));
		srand(seed);
		test.placeItem();
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
		ptdr->run(WIDTH_WINDOW, HEIGHT_WINDOW);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
    return 0;
}
