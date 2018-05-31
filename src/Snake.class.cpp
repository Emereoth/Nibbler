/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:16:06 by acottier          #+#    #+#             */
/*   Updated: 2018/05/31 15:10:20 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Snake.class.hpp"

Snake::Snake(Map & map) : _map(map)
{
	(void)_map;
}

Snake::~Snake()
{
}

std::list<snakeInfo>	Snake::getSnake(void) const
{
	return (_snake);
}

void				Snake::grow(void)
{
	// TODO SHIT
}

void				Snake::updatePos(int key)
{
	std::list<snakeInfo>::iterator		it = _snake.begin();
	std::list<snakeInfo>::iterator		end = _snake.end();
	unsigned char						prevOrigin = (*it).origin;

	(void)prevOrigin;
	while (it != end)
	{
		if (it == _snake.begin())
		{

		}
		// else if (*it == _snake.back())
		// {

		// }
		else
		{
			
		}
	}
	updateExtremity(key, it);
}

void				Snake::updateExtremity(int key, std::list<snakeInfo>::iterator it)
{
	if ( it == _snake.begin() && key && (*it).destination + key != 4 && (*it).destination + key != 9)
		(*it).destination = (*it).origin = key;
	switch ((*it).origin)
	{
		case (UP) :
		{
			(*it).pos[1]--;
			break ;
		}
		case (DOWN) :
		{
			(*it).pos[1]++;
			break ;
		}
		case (RIGHT) :
		{
			(*it).pos[0]++;
			break ;
		}
		case (LEFT) :
		{
			(*it).pos[0]--;
			break;
		}
	}
}

bool			Snake::update(int input)
{
	(void)input;
	// return value : true if food is eaten
	return (false);
}