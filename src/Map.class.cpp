/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:19:36 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/21 13:48:14 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Map.class.hpp"

Map::Map(void)
{
	std::ifstream		file;
	std::string			line;

	file.open("map.txt");
	for (size_t x = 0; x < 62; x++)
	{
		getline(file, line);
		for (size_t y = 0; y < line.size(); y++)
			map[x][y] = line[y];
	}
	file.close();
}

Map::~Map(void)
{
	return ;
}

void				Map::displayMap(void) const
{
	for (size_t i = 0; i < 62; i++)
	{
		for (size_t j = 0; j < 62; j++)
			std::cout << ((char)map[i][j] == '0' ? (char)32 : (char)'1');
		std::cout << std::endl;
	}
}

void				Map::placeItem(void)
{
	int						zoneStart[2] = {1, 1};
	std::array<int, 2>		startObstacle;
	bool					preset;

	for (size_t i = 0; i < 6; i++)
	{
		preset = rand() % 2;
		startObstacle = generateItem(zoneStart, preset);
		// std::cout << startObstacle[0] << std::endl;
		// std::cout << startObstacle[1] << std::endl;
		updateMap(startObstacle);
		zoneStart[0] += 20;
		if (zoneStart[0] >= 60)
			zoneStart[1] += 30;
		zoneStart[0] %= 59;
		_obstacle.clear();
	}
	displayMap();
}

void				Map::updateMap(std::array<int, 2> start)
{
	for (size_t i = 0; i < _obstacle.size(); i++)
	{
		for (size_t j = 0; j < _obstacle[i].size(); j++)
		{
			// std::cout << "start[0 + i] => " << start[0] + i << std::endl;
			// std::cout << "start[1 + j] => " << start[1] + j << std::endl;
				map[start[0] + i][start[1] + j] = _obstacle[i][j] + 48;
			// std::cout << "new value: " << map[start[0] + i][start[1] + j] << std::endl;
		}

	}
}

std::array<int, 2>	Map::generateItem(int zoneStart[2], bool preset)
{
	std::array<int, 2>		res = { {1,1} };

	std::cout << "point de depart zone y "  << zoneStart[0] << std::endl;
	std::cout << "point de depart zone x " << zoneStart[1] << std::endl;
	if (preset)
		generatePreset();
	else
		generateRand();
	std::cout << "taille obstacle actuel (y) " << _obstacle.size() << std::endl;
	std::cout << "taille obstacle actuel (x) " << _obstacle[0].size() << std::endl;;
	res[0] = (rand() % (19 - _obstacle.size())) + zoneStart[0];
	res[1] = (rand() % (29 - _obstacle[0].size())) + zoneStart[1];
	std::cout << "point de depart obstacle y " << res[0] << std::endl;
	std::cout << "point de depart obstacle x " << res[1] << std::endl;
	return (res);
}

void				Map::generatePreset(void)
{
	int				random = rand() % 3 + 1;

	if (random == 1)
		_obstacle = Preset::type1();
	if (random == 2)
		_obstacle = Preset::type2();
	if (random == 3)
		_obstacle = Preset::type3();
}

void				Map::generateRand(void)
{
	size_t				xRand;
	size_t				yRand;
	std::vector<int> 	temp;

	xRand = rand() % 8 + 3;
	yRand = rand() % 8 + 3;
	// std::cout << "Taille x obstacle random " << xRand << std::endl;
	// std::cout << "Taille y obstacle random " << yRand << std::endl;
	for (size_t i = 0; i < xRand; i++)
	{
		for (size_t j = 0; j < yRand; j++)
			temp.push_back(rand() % 2);
			// temp.push_back((rand() % 2) == 0 ? 2 : 1);
		_obstacle.push_back(temp);
		temp.clear();
	}
}