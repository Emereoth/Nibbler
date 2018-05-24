#include <iostream>
#include <dlfcn.h>
#include "../inc/Api.class.hpp"
#include "../inc/lib.namespace.hpp"
#include "../inc/Map.class.hpp"
#include "../inc/Snake.class.hpp"
#include <fcntl.h>

int main(int ac, char **av)
{
	try
	{
		Snake					snake;
		Map						map(snake);
		unsigned int			seed;

		read(open("/dev/urandom", O_RDONLY), &seed, sizeof(seed));
		srand(seed);
		map.placeItem();
		std::string			opt(manageOpt::getOpt(ac, av));
		std::string			optPath(manageOpt::getPathLib(opt));

		void				*entryPoint;
		AGraphics			*(*func)(size_t, size_t, float);

		entryPoint = dlopen(optPath.c_str(), RTLD_NOW);
		if (!entryPoint)
		{
			std::cerr << dlerror() << std::endl;
			return (-1);
		}
		func = (AGraphics *(*)(size_t, size_t, float))dlsym(entryPoint, "create");
		if (!func)
			std::cerr << dlerror() << std::endl;
		AGraphics		*lib = func(1920, 1080, 1080.0f / 62.0f);
		lib->openWindow();
		while (lib->isOpen())
		{
			lib->keyPress();
			lib->draw(map);
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
    return 0;
}
