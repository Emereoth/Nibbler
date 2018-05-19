/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 15:16:24 by acottier          #+#    #+#             */
/*   Updated: 2018/05/17 17:20:55 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <dlfcn.h>
#include "../inc/Api.class.hpp"
#include "../sdl_lib/SDL/include/SDL.h"

int		main(void)
{
	void		*lib;
	Api			*(*tmp)();

	lib = dlopen("../sdl_lib/SDL.so", RTLD_NOW);
	if (!lib)
		std::cerr << dlerror() << std::endl;
	tmp = (Api *(*)())dlsym(lib, "create");
	if (!tmp)
		std::cerr << dlerror() << std::endl;
	Api			*api = tmp();
	api->run(1920, 1080);
}