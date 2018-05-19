/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Preset.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:25:10 by acottier          #+#    #+#             */
/*   Updated: 2018/05/19 18:32:33 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Preset.class.hpp"
#include <fcntl.h>
#include <unistd.h>

Preset::Preset(void)
{
}

Preset::~Preset(void)
{
}

std::vector<std::vector<int>>	Preset::type1(void)
{
	int					size;

	size = (rand() % 6) + 1;
	std::cout << "size: " << size << std::endl;
	std::vector<std::vector<int>>	obstacle;
	for (int i = 0 ; i < (3 + size * 2) ; i++)
	{
		std::vector<int>	tmp;
		for (int j = 0 ; j < (3 + size * 2) ; j++)
		{
			if (i <= size && (j == size || j == size + 2) && i + size >= 1) // HAUT
				tmp.push_back(1);
			else if (i > size + 1 && (j == size || j == size + 2) && i - size < 9) // BAS
				tmp.push_back(1);
			else if (j <= size && (i == size || i == size + 2) && j + size >= 1) // GAUCHE
				tmp.push_back(1);
			else if (j > size + 1 && (i == size || i == size + 2) && j - size < 9) // DROITE
				tmp.push_back(1);
			else
				tmp.push_back(0);
		}
		obstacle.push_back(tmp);
	}


	for (size_t i = 0 ; i < obstacle.size() ; i++)
	{
		for (size_t j = 0 ; j < obstacle[i].size() ; j++)
			std::cout << obstacle[i][j];
		std::cout << std::endl;
	}

	return (obstacle);
}