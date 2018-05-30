#include <iostream>
#include <dlfcn.h>
#include "../inc/Api.class.hpp"
#include "../inc/Map.class.hpp"
#include "../inc/Snake.class.hpp"
#include <fcntl.h>
#include <regex>
#include <sstream>
#include <string>
#include <unistd.h>

namespace {

	class Error : public std::exception {

		public:

			Error(void) = default;
			Error(Error &src) = default;
			virtual ~Error(void) {};

			Error				&operator=(const Error &rhs) = delete;

			class optNotFound : public std::exception {
				public:
					virtual const char *what() const throw()
					{
						return ("Library not found !");
					}
			};

			class tooManyArguments : public std::exception {
				public:
					virtual const char *what() const throw()
					{
						return ("Too many arguments !");
					}
			};

			class optBadFormat : public std::exception {
				public:
					virtual const char *what() const throw()
					{
						return ("usage:\n[--lib=opengl|sfml|sdl] [--size=width*height]");
					}
			};

			class WindowTooSmall : public std::exception {
				public:
					virtual const char *what() const throw()
					{
						return ("Window too small!");
					}
			};

	};

	class Opt {

		public:

			Opt();
			Opt(Opt const &src) = default;
			Opt(int ac, char **av);
			~Opt();

			size_t			width;
			size_t			height;
			float			squareSize;
			std::string		lib;

		private:

			Opt				&operator=(Opt const &rhs);

			size_t			getWidth(int ac, char **av);
			size_t			getHeight(int ac, char **av);
			std::string		getLib(int ac, char **av);
			std::string		randLib();
			std::string		getPathLib(std::string const &lib);

			
	};

	Opt::~Opt() {};

	Opt::Opt() : width(1920), height(1080), squareSize(1080 / 62.0f), lib(randLib()) {};

	Opt::Opt(int ac, char **av)
	{
		int				i = 1;
		std::cmatch		match;
		std::regex		reg("(^--)([a-z]+)((=?)([a-z]+|[0-9]+(x)[0-9]+))?(.*)");

		if (ac > 3)
			throw Error::tooManyArguments();
		lib = randLib();
		width = 1920;
		height = 1080;
		squareSize = 1080 / 62.0f;
		while (i < ac)
		{
			if (std::regex_match(av[i], match, reg))
			{
				if (!match[2].str().compare("lib"))
					lib = getPathLib(match[5].str());
				else if (!match[2].str().compare("size"))
				{
					std::stringstream		stream(match[5].str());
					std::string				size;

					getline(stream, size, 'x');
					width = std::stoi(size);
					getline(stream, size, 'x');
					height = std::stoi(size);
					if ((squareSize = (width > height ? height / 62.0f : width / 62.0f)) < 10)
						throw Error::WindowTooSmall();
				}
				else
					throw Error::optBadFormat();
			}
			i++;
		}
	}

	std::string			Opt::randLib()
	{
		int								nb;
		std::vector<std::string>		allLib = {"opengl", "sdl", "sfml"};

		srand(time(NULL));
		nb = rand() % 3;
		return (getPathLib(allLib[nb]));
	}

	std::string			Opt::getPathLib(std::string const &opt)
	{
		if (!opt.compare("opengl"))
			return (std::string("openGL_lib/opengl.so"));
		else if (!opt.compare("sfml"))
			return (std::string("sfml_lib/sfml.so"));
		else if (!opt.compare("sdl"))
			return (std::string("sdl_lib/SDL.so"));
		throw Error::optNotFound();
	}

	Opt				getOpt(int ac, char **av)
	{
		if (ac == 1)
			return (Opt());
		return (Opt(ac, av));
	}
}

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
		(void)ac;
		(void)av;
		Opt					opt = getOpt(ac, av);

		void				*entryPoint;
		AGraphics			*(*func)(size_t, size_t, float);

		entryPoint = dlopen(opt.lib.c_str(), RTLD_NOW);
		if (!entryPoint)
		{
			std::cerr << dlerror() << std::endl;
			return (-1);
		}
		func = (AGraphics *(*)(size_t, size_t, float))dlsym(entryPoint, "create");
		if (!func)
		{
			std::cerr << dlerror() << std::endl;
			return (-1);
		}
		AGraphics		*lib = func(opt.width, opt.height, opt.squareSize);
		lib->openWindow();
		while (lib->isOpen())
		{
			lib->keyPress();
			lib->draw(map);
			std::cout << "fuck you" << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
    return 0;
}
