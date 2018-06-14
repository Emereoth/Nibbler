
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:16:06 by acottier          #+#    #+#             */
/*   Updated: 2018/06/09 12:45:25 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Snake.class.hpp"
#include <random>

Snake::Snake(Map &map) :
	size(4),
	eatFood(false),
	_map(map),
	_convertKey {
		{key::UP, UP},
		{key::DOWN, DOWN},
		{key::LEFT, LEFT},
		{key::RIGHT, RIGHT},
	},
	_spriteForKey {
		{UP_LEFT, sprite::BODY_UP_LEFT},
		{UP_RIGHT, sprite::BODY_UP_RIGHT},
		{DOWN_LEFT, sprite::BODY_DOWN_LEFT},
		{DOWN_RIGHT, sprite::BODY_DOWN_RIGHT},
		{UP, sprite::HEAD_UP},
		{DOWN, sprite::HEAD_DOWN},
		{LEFT, sprite::HEAD_LEFT},
		{RIGHT, sprite::HEAD_RIGHT},
	},
	_moveForKey {
		{UP, -62},
		{DOWN, 62},
		{LEFT, -1},
		{RIGHT, 1}
	}
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
	pushPartSnake(sprite::TAIL_LEFT, LEFT, LEFT, index + 3);
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
	int					start = index - 10;

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

void				Snake::grow(void)
{
	size++;
	// TODO SHIT
}

bool				Snake::updatePos(key keyPress)
{
	int				convertKey = _convertKey[keyPress];

	if (keyPress == key::NO
	|| (_snake[0].origin <= DOWN && convertKey <= DOWN)
	|| (_snake[0].origin > DOWN && convertKey > DOWN))
		convertKey = _snake[0].origin;
	else if ((_snake[0].origin <= DOWN && convertKey > DOWN) || (_snake[0].origin > DOWN && convertKey <= DOWN))
	{
		snakeInfo	newPart;

		newPart.pos = _snake[0].pos;
		newPart.origin = convertKey;
		newPart.destination = (_snake[0].origin ^ 255) + convertKey;
		newPart.sprite = _spriteForKey[newPart.destination];
		_snake.insert(_snake.begin() + 1, newPart);
	}
	if (collider(convertKey))
		return (true);
	updateExtremities(convertKey);
	updateMap(convertKey);
	return (false);
}

bool				Snake::collider(int key)
{
	int				pos = _snake[0].pos + _moveForKey[key];

	if (_map.map[pos] == sprite::FOOD)
	{
		eatFood = true;
		size++;
	}
	else if (_map.map[pos] != sprite::SOIL && _map.map[pos] != sprite::FOOD)
		return true;
	return false;
}

void				Snake::updateExtremities(int key)
{
	int				move = _moveForKey[key];
	size_t			size = _snake.size() - 1;

	_snake[0].origin = key;
	_snake[0].destination = key;
	_snake[0].sprite = _spriteForKey[key];
	_snake[0].pos += move;
	if (!eatFood)
	{
		_map.map[_snake[size].pos] = sprite::SOIL;
		_snake[size].pos += _moveForKey[_snake[size].origin];
		if (_snake[size - 1].pos == _snake[size].pos)
		{
			_snake[size].origin = _snake[size - 1].origin;
			if (_snake[size].origin == LEFT)
				_snake[size].sprite = sprite::TAIL_LEFT;
			else if (_snake[size].origin == RIGHT)
				_snake[size].sprite = sprite::TAIL_RIGHT;
			else if (_snake[size].origin == DOWN)
				_snake[size].sprite = sprite::TAIL_UP;
			else if (_snake[size].origin == UP)
				_snake[size].sprite = sprite::TAIL_DOWN;
			_snake.erase(_snake.begin() + size - 1);
		}
	}
}

void				Snake::updateMap(int key)
{
	size_t			delta = 0;
	size_t			sizeSnake = _snake.size();
	int				move;

	(void)key;
	for (size_t i = 0; i < sizeSnake; i++)
	{
		_map.map[_snake[i].pos] = _snake[i].sprite;
		if (i + 1 < sizeSnake)
		{
			move = _moveForKey[_snake[i + 1].origin];
			delta = std::abs(_snake[i + 1].pos - _snake[i].pos) / std::abs(move);
			for (size_t j = 1; j < delta; j++)
			{
				if (_snake[i + 1].origin == LEFT || _snake[i + 1].origin == RIGHT)
					_map.map[_snake[i].pos - move] = sprite::BODY_H;
				else
					_map.map[_snake[i].pos - move] = sprite::BODY_V;
			}
		}
	}
}