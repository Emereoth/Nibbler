/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:17:24 by acottier          #+#    #+#             */
/*   Updated: 2018/06/11 16:43:24 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <array>
#include <map>
#include <list>
#include "Map.class.hpp"
#include "Api.class.hpp"

enum	 snakeOrientation
{
	UP = 1,
	DOWN = UP ^ 255, // 254
	RIGHT = DOWN + 2, // 256
	LEFT = RIGHT ^ 255 // 511
};

enum	 snakeCombinedOrientation
{
	UP_LEFT = UP + LEFT, // 512
	UP_RIGHT = UP + RIGHT, // 257
	DOWN_LEFT = LEFT + DOWN, // 765
	DOWN_RIGHT = DOWN + RIGHT // 510
};

struct snakeInfo
{
	int				pos;
	int				origin;
	int				destination;
	sprite			sprite;
};

class Snake
{
	public:

		explicit Snake(Map & map);
		virtual ~Snake(void);

		std::vector<snakeInfo>	getSnake(void) const;
		void					grow(void);
		void					updatePos(key keyPress);
		
		int						size;

	private:
	
		explicit Snake(void) = default;
		Snake(const Snake &) = default;
		Snake &operator=(const Snake &) = default;

		void					pushPartSnake(sprite sprite, int origin, int dest, int pos);
		void					updateExtremities(int key);
		bool					isPlace(int index) const;
		void					updateMap(int mvoe);

		std::vector<snakeInfo>	_snake;
		bool					_eatFood;
		Map						&_map;
		std::map<key, int>		_convertKey;
		std::map<int, sprite>	_spriteForKey;
		std::map<int, int>		_moveForKey;

};

#endif