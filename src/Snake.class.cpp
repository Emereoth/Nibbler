/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:16:06 by acottier          #+#    #+#             */
/*   Updated: 2018/06/02 12:10:03 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Snake.class.hpp"
#include <random>

Snake::Snake(Map &map) : _map(map)
{
	std::random_device				rd;
	std::mt19937					gen(rd());
	std::uniform_int_distribution<> pos(62 * 3, SIZE_MAP - (62 * 3));
	int								index = pos(gen);
	size_t							sizeSnake;
	size_t							delta = 0;

	while (!isPlace(index))
		index = pos(gen);
	pushPartSnake(sprite::HEAD_LEFT, LEFT, LEFT, index);
	pushPartSnake(sprite::TAIL_LEFT, LEFT, LEFT, index + 4);
	sizeSnake = _snake.size();
	for (size_t i = 0; i < sizeSnake; i++)
	{
		_map.map[_snake[i].pos] = _snake[i].sprite;
		if (i + 1 < sizeSnake)
			delta = _snake[i + 1].pos - _snake[i].pos;
		for (size_t j = 1; j < delta; j++)
			_map.map[_snake[i].pos + j] = sprite::BODY_H;
		delta = 0;
	}
}

bool					Snake::isPlace(int index) const
{
	int					start = index - 8;

	while (start < index + 5)
	{
		if (_map.map[start] == sprite::WALL)
			return (false);
		start++;
	}
	return (true);
}

void					Snake::pushPartSnake(sprite sprite, int origin, int dest, int pos)
{
	snakeInfo			snake;

	snake.pos = pos;
	snake.origin = origin;
	snake.destination = dest;
	snake.sprite = sprite;
	_snake.push_back(snake);
}

Snake::~Snake()
{
}

std::vector<snakeInfo>	Snake::getSnake(void) const
{
	return (_snake);
}

void				Snake::grow(void)
{
	// TODO SHIT
}

void				Snake::updatePos(int key)
{
	// std::list<snakeInfo>::iterator		it = _snake.begin();
	// std::list<snakeInfo>::iterator		end = _snake.end();
	// unsigned char						prevOrigin = (*it).origin;

	// (void)prevOrigin;
	// while (it != end)
	// {
	// 	if (it == _snake.begin())
	// 	{

	// 	}
	// 	// else if (*it == _snake.back())
	// 	// {

	// 	// }
	// 	else
	// 	{
			
	// 	}
	// }
	// updateExtremity(key, it);
	(void)key;
}

void				Snake::updateExtremity(int key, std::list<snakeInfo>::iterator it)
{
	// if ( it == _snake.begin() && key && (*it).destination + key != 4 && (*it).destination + key != 9)
	// 	(*it).destination = (*it).origin = key;
	// switch ((*it).origin)
	// {
	// 	case (UP) :
	// 	{
	// 		(*it).pos[1]--;
	// 		break ;
	// 	}
	// 	case (DOWN) :
	// 	{
	// 		(*it).pos[1]++;
	// 		break ;
	// 	}
	// 	case (RIGHT) :
	// 	{
	// 		(*it).pos[0]++;
	// 		break ;
	// 	}
	// 	case (LEFT) :
	// 	{
	// 		(*it).pos[0]--;
	// 		break;
	// 	}
	// }
	(void)key;(void)it;
}

bool			Snake::update(int input)
{
	(void)input;
	// return value : true if food is eaten
	return (false);
}