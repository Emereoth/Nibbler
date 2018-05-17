/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.namespace.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:58:27 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/17 15:14:46 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <regex>

namespace manageOpt {

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
						return ("Wrong option format !");
					}
			};

		private:

	};

	std::string			randLib(void)
	{
		int								nb;
		std::vector<std::string>		allLib = {"opengl", "sdl", "sfml"};

		srand(time(NULL));
		nb = rand() % 3;
		std::cout << allLib[nb] << std::endl;
		return (allLib[nb]);
	}

	std::string			getOpt(int ac, char **av)
	{
		std::cmatch		match;
		std::regex		reg("(^--)([a-z]+)(=)([a-z]+)(.*)");

		if (ac > 2)
			throw Error::tooManyArguments();
		if (ac == 2)
		{
			if (std::regex_match(av[1], match, reg))
			{
				if (match[2].str().compare("lib"))
					throw Error::optBadFormat();
				return (match[4].str());
			}
		}
		return (manageOpt::randLib());
	}

	std::string			getPathLib(std::string &opt)
	{
		if (!opt.compare("opengl"))
			return (std::string("openGL_lib/opengl.so"));
		if (!opt.compare("sfml"))
			return (std::string("sfml_lib/sfml.so"));
		if (!opt.compare("sdl"))
			return (std::string("sdl_lib/SDL.so"));
		throw Error::optNotFound();
	}
}