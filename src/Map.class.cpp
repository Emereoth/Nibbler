/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:19:36 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/19 15:20:31 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Map.class.hpp"

Map::Map(void)
{
	std::ifstream		file;
	std::string			line;

	file.open("map.txt");
	for (int x = 0; x < 62; x++)
	{
		getline(file, line);
		for (int y = 0; y < line.size(); y++)
			map[x][y] = line[y];
	}
	file.close();
}