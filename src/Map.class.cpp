/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:19:36 by rvievill          #+#    #+#             */
/*   Updated: 2018/06/18 13:37:30 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Map.class.hpp"
#include <random>

Map::Map() :
	_obstacle {},
	offsetMap(62)
{
	generateBasicMap();
	placeItem();
}

Map::~Map(void)
{
	return ;
}

void				Map::generateBasicMap()
{
	for (size_t i = 0; i < 3844; i++)
	{
		if (i / 62 == 0 || i / 62 == 61)
			map[i] = sprite::WALL;
		else if (i % 62 == 0 || i % 62 == 61)
			map[i] = sprite::WALL;
		else
			map[i] = sprite::SOIL;
	}
}

void				Map::displayMap(void) const
{
	size_t			size = 62 * 62;

	for (size_t i = 0; i < size; i++)
	{
		if (i > 0 && i % offsetMap == 0)
			std::cout << std::endl;
		std::cout << static_cast<int>(map[i]);
	}
	std::cout << std::endl;
}

void				Map::placeItem(void)
{
	size_t					zoneStart[2] = {0, 0};
	std::array<size_t, 2>	startObstacle;
	bool					Map;

	for (size_t i = 0; i < 6; i++)
	{
		Map = rand() % 2;
		startObstacle = generateItem(zoneStart, Map);
		updateMap(startObstacle);
		zoneStart[0] += 20;
		if (zoneStart[0] >= 60)
			zoneStart[1] += 30;
		zoneStart[0] %= 59;
	}
	// displayMap();
}

void				Map::updateMap(std::array<size_t, 2> &start)
{
	size_t		xStart = start[0];
	size_t		yStart = start[1];
	
	for (size_t i = 0 ; i < 19 ; i++)
	{
		for (size_t j = 0 ; j < 29 ; j++)
		{
			if (_obstacle[i][j] == sprite::WALL)
			{
				int posInMap = (yStart + i) * 62 + xStart + j;
				if (posInMap < 3844)
					map[posInMap] = sprite::WALL;
			}
		}
	}
	clearObstacle();
}

std::array<size_t, 2>	Map::generateItem(size_t (&zoneStart)[2], bool Map)
{
	std::array<size_t, 2>		res;
	std::array<size_t, 2>		size;

	if (Map)
		size = generatePreset();
	else
		size = generateRand();
	res[0] = (rand() % (19 - size[0])) + zoneStart[0];
	res[1] = (rand() % (29 - size[1])) + zoneStart[1];
	return (res);
}

std::array<size_t, 2>				Map::generatePreset(void)
{
	size_t				random = rand() % 3 + 1;

	if (random == 1)
		return (preset1());
	else if (random == 2)
		return (preset2());
	else
		return (preset3());
}

std::array<size_t, 2>				Map::generateRand(void)
{
	std::array<size_t, 2>				size;
	std::random_device				rd;
	std::mt19937					gen(rd());
	std::uniform_int_distribution<> startObstacle(3, 11);
	std::uniform_int_distribution<> wallObstacle(0, 1);

	size[0] = startObstacle(gen);
	size[1] = startObstacle(gen);
	for (size_t i = 0; i < size[0]; i++)
	{
		for (size_t j = 0; j < size[1]; j++)
			_obstacle[i][j] = wallObstacle(gen) == 1 ? sprite::WALL : sprite::SOIL;
	}
	return (size);
}

std::array<size_t, 2>					Map::preset1(void)
{
	size_t								randSize;
	std::array<size_t, 2>				size;
	
	randSize = (rand() % 6) + 1;
	size[0] = size[1] = 3 + randSize * 2;
	for (size_t i = 0 ; i < (3 + randSize * 2) ; i++)
	{
		for (size_t j = 0 ; j < (3 + randSize * 2) ; j++)
		{
			if (i <= randSize && (j == randSize || j == randSize + 2) && i + randSize >= 1) // HAUT
				_obstacle[i][j] = sprite::WALL;
			else if (i > randSize + 1 && (j == randSize || j == randSize + 2) && i - randSize < 9) // BAS
				_obstacle[i][j] = sprite::WALL;
			else if(j <= randSize && (i == randSize || i == randSize + 2) && j + randSize >= 1) // GAUCHE
				_obstacle[i][j] = sprite::WALL;
			else if (j > randSize + 1 && (i == randSize || i == randSize + 2) && j - randSize < 9) // DROITE
				_obstacle[i][j] = sprite::WALL;
		}
	}
	return (size);
}

std::array<size_t, 2>					Map::preset2(void)
{
	size_t								randSize;
	std::array<size_t, 2>				size;
	
	randSize = (rand() % 6) + 1;
	size[0] = size[1] = 3 + randSize * 2;
	for (size_t i = 0 ; i < (3 + randSize * 2) ; i++)
	{
		for (size_t j = 0 ; j < (3 + randSize * 2)  ; j++)
		{
			if ((i == 0 || i == (3 + randSize * 2) - 1) && j != randSize + 1) // RANGEES
				_obstacle[i][j] = sprite::WALL;
			else if ((j == 0 || j == (3 + randSize * 2) -1) && i != randSize + 1 ) // COLONNES
				_obstacle[i][j] = sprite::WALL;
		}
	}
	return (size);
}

std::array<size_t, 2>					Map::preset3(void)
{
	size_t								randSize;
	std::array<size_t, 2>				size;
	
	randSize = (rand() % 5) + 1;
	size[0] = size[1] = 5 + randSize * 2;
	for (size_t i = 0 ; i < (5 + randSize * 2) ; i++)
	{
		for (size_t j = 0 ; j < (5 + randSize * 2)  ; j++)
		{
			if (i == randSize + 2 || j == randSize + 2)				// COLONNE + LIGNE CENTRALE
				_obstacle[i][j] = sprite::WALL;
			else if (i != 0 && i != (5 + randSize * 2) - 1 && j != 0 && j != (5 + randSize * 2) - 1 // PAS SUR BORDURE
				&& i != randSize + 1 && i != randSize + 3 && j != randSize + 1 && j != randSize + 3) // MARGE INTERIEURE
				_obstacle[i][j] = sprite::WALL;
		}
	}
	return (size);
}

void									Map::clearObstacle(void)
{
	for (size_t i =0; i < 19; i++)
	{
		for (size_t j = 0; j < 29; j++)
		{
			_obstacle[i][j] = sprite::SOIL;
		}
	}
}