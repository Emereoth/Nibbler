#include <iostream>
#include "Api.class.hpp"
#include "Map.class.hpp"
#include "Nibbler.class.hpp"
#include <regex>
#include <sstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>

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
			bool			debug;
			std::string		lib;

		private:

			Opt				&operator=(Opt const &rhs);

			size_t			getWidth(int ac, char **av);
			size_t			getHeight(int ac, char **av);
			std::string		getLib(int ac, char **av);
			std::string		randLib();
			std::string		getPathLib(std::string const &lib);
			std::string		getPathNibbler();
			

			
	};

	std::string				Opt::getPathNibbler()
	{
		std::string		pathApp(std::getenv("HOME"));
	
		return (pathApp + "/Library/nibbler/");		
	}


	Opt::~Opt() {};

	Opt::Opt() : width(1920), height(1080), squareSize(1080 / 62.0f), debug(false), lib(randLib()) {};

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
				if (!match[2].str().compare("debug"))
					debug = true;
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
					if (width > 1980)
						width = 1980;
					if (height > 1080)
						height = 1080;
					if ((squareSize = (width > height ? height / 62.0f : width / 62.0f)) < 10)
						throw Error::WindowTooSmall();
				}
			}
			else
				throw Error::optBadFormat();
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
			return (getPathNibbler() + std::string("openGL_lib/opengl.so"));
		else if (!opt.compare("sfml"))
			return (getPathNibbler() + std::string("sfml_lib/sfml.so"));
		else if (!opt.compare("sdl"))
			return (getPathNibbler() + std::string("sdl_lib/SDL.so"));
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
		Opt						opt = getOpt(ac, av);
		Nibbler					nibbler(opt.lib.c_str(), opt.width, opt.height, opt.squareSize, opt.debug);
		Map						map;
		unsigned int			seed;

		std::cout << opt.debug << std::endl;
		read(open("/dev/urandom", O_RDONLY), &seed, sizeof(seed));
		srand(seed);
		nibbler.run(map);

	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
    return 0;
}
