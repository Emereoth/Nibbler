/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:16:06 by acottier          #+#    #+#             */
/*   Updated: 2018/05/21 18:42:34 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Snake.class.hpp"

Snake::Snake()
{
}

Snake::~Snake()
{
}

std::list<data &>	Snake::getSnake(void) const
{
	return (_snake);
}

void				Snake::grow(void)
{
	// TODO SHIT
}

void				Snake::updatePos(int key)
{
	std::list<data &>::iterator		it = _snake.begin();
	unsigned char					prevOrigin = (*it).origin;

	while (it != _snake.end())
	{
		if (it == _snake.begin())
		{

		}
		else if (*it == _snake.back())
		{

		}
		else
		{
			
		}
	}
	updateExtremity(key, it);
}

void				Snake::updateExtremity(int key, std::list<data &>::iterator it)
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