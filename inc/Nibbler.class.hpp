/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:39:31 by rvievill          #+#    #+#             */
/*   Updated: 2018/06/07 13:07:20 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_HPP
# define NIBBLER_HPP

# include "../inc/Api.class.hpp"
# include "../inc/Map.class.hpp"
#include "../inc/Snake.class.hpp"

class Nibbler {

	private:

		Nibbler(void) = default;
		Nibbler(Nibbler const &src) = default;

		Nibbler			&operator=(Nibbler const &rhs) = default;		

		void			switchLib(libName lib);

	public:

		explicit Nibbler(const char *pathLib, size_t width, size_t height, float squareSize);

		void			run(Map &map);

		AGraphics		*window;

};

#endif