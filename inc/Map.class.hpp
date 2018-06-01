/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:50:15 by rvievill          #+#    #+#             */
/*   Updated: 2018/06/01 13:20:56 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <unistd.h>

enum class	sprite
{
	SOIL,
	WALL,
	HEAD_UP,
	HEAD_DOWN,
	HEAD_LEFT,
	HEAD_RIGHT,
	BODY_H,
	BODY_V,
	TAIL_UP,
	TAIL_DOWN,
	TAIL_LEFT,
	TAIL_RIGHT,
	BODY_UP_LEFT,
	BODY_UP_RIGHT,
	BODY_DOWN_LEFT,
	BODY_DOWN_RIGHT,
	FOOD
};

class Map {

	private:

		explicit 							Map(const Map &src) = delete;
		Map									&operator=(const Map &rhs) = delete;

		std::array<size_t, 2>				generateItem(size_t (&zoneStart)[2], bool preset);
		std::array<size_t, 2>				generatePreset(void);
		std::array<size_t, 2>				preset1(void);
		std::array<size_t, 2>				preset2(void);
		std::array<size_t, 2>				preset3(void);
		std::array<size_t, 2>				generateRand(void);
		void								updateMap(std::array<size_t, 2> &start);
		// bool								checkCollision(std::list<snakeInfo> snake) const;
		void								clearObstacle(void);


		sprite								_obstacle[19][29];

	public:

		explicit 							Map(void);
		~Map(void);

		void								placeItem(void);
		void								displayMap(void) const;

		int									offsetMap;
		sprite								map[62 * 62];

};

#endif