/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:50:15 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/28 12:09:21 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <unistd.h>
#include "../inc/Preset.class.hpp"
#include "../inc/Snake.class.hpp"

class Map {

	public:

		explicit 							Map(void);
		explicit							Map(Snake &snake);
		~Map(void);

		void								placeItem(void);
		void								displayMap(void) const;

		int									map[62][62];

	private:

		explicit 							Map(const Map &src) = delete;
		Map									&operator=(const Map &rhs) = delete;

		std::array<int, 2>					generateItem(int zoneStart[2], bool preset);
		void								generatePreset(void);
		void								generateRand(void);
		void								updateMap(std::array<int, 2> start);
		bool								checkCollision(std::list<snakeInfo> snake) const;

		std::vector<std::vector<int>>		_obstacle;
		Snake								&_snake;
};

#endif