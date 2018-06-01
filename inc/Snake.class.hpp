/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:17:24 by acottier          #+#    #+#             */
/*   Updated: 2018/06/01 10:43:55 by rvievill         ###   ########.fr       */
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
	std::array<int, 2>								pos;
	unsigned char									origin;
	unsigned char									destination;
	bool											grow;
	// std::map<snakeCombinedOrientation, std::string>	spriteMap = 
	// {
	// 	{UP_LEFT, "upleft.png"},
	// 	{UP_RIGHT, "upright.png"},
	// 	{DOWN_LEFT, "downleft.png"},
	// 	{DOWN_RIGHT, "downright.png"}
	// };
};

class Snake
{
	public:

		explicit Snake(Map & map);
		virtual ~Snake(void);

		std::list<snakeInfo>	getSnake(void) const;
		void					grow(void);
		void					updatePos(int key = 0);
		bool					update(int input);

	private:
	
		explicit Snake(void) = default;
		Snake(const Snake &) = default;
		Snake &operator=(const Snake &) = default;

		void				updateExtremity(int key, std::list<snakeInfo>::iterator it);
		bool				checkCollid();

		std::list<snakeInfo>	_snake;
		Map						&_map;

};

#endif