/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:17:24 by acottier          #+#    #+#             */
/*   Updated: 2018/06/02 12:52:23 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <array>
#include <map>
#include <list>
#include "Map.class.hpp"

enum	 snakeOrientation
{
	UP = 1,
	DOWN = 3,
	RIGHT,
	LEFT
};

enum	 snakeCombinedOrientation
{
	UP_LEFT = 5,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

struct snakeInfo
{
	int				pos;
	unsigned char	origin;
	unsigned char	destination;
	sprite			sprite;
};

class Snake
{
	public:

		explicit Snake(Map & map);
		virtual ~Snake(void);

		std::vector<snakeInfo>	getSnake(void) const;
		void					grow(void);
		void					updatePos(int key = 0);
		bool					update(int input);

	private:
	
		explicit Snake(void) = default;
		Snake(const Snake &) = default;
		Snake &operator=(const Snake &) = default;

		void					updateExtremity(int key, std::list<snakeInfo>::iterator it);
		void					pushPartSnake(sprite sprite, int origin, int dest, int pos);
		bool					isPlace(int index) const;

		std::vector<snakeInfo>	_snake;
		Map						&_map;

};

#endif