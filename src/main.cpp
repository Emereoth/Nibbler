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
		// Map					test;
		unsigned int			seed;

		read(open("/dev/urandom", O_RDONLY), &seed, sizeof(seed));
		srand(seed);
		// test.placeItem();
		std::string			opt(manageOpt::getOpt(ac, av));
		std::string			optPath(manageOpt::getPathLib(opt));

		void				*entryPoint;
		AGraphics			*(*func)(size_t, size_t, size_t);

		entryPoint = dlopen(optPath.c_str(), RTLD_NOW);
		if (!entryPoint)
		{
			std::cerr << dlerror() << std::endl;
			return (-1);
		}
		func = (AGraphics *(*)(size_t, size_t, size_t))dlsym(entryPoint, "create");
		if (!func)
			std::cerr << dlerror() << std::endl;
		AGraphics		*lib = func(1920, 1080, 1080 / 60);
		lib->openWindow();
		while (lib->isOpen())
		{
			lib->keyPress();
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
    return 0;
}
