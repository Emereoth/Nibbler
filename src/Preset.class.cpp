/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Preset.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:25:10 by acottier          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/05/21 12:04:39 by acottier         ###   ########.fr       */
=======
/*   Updated: 2018/05/19 18:32:33 by rvievill         ###   ########.fr       */
>>>>>>> 390948fda3e0e5258a2e26b9a024de0cad0d346b
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
	int								size;
	unsigned int					seed;
	std::vector<std::vector<int>>	obstacle;
	int					size;

	size = (rand() % 6) + 1;
	std::cout << "size: " << size << std::endl;
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
	return (obstacle);
}

std::vector<std::vector<int>>	Preset::type2(void) const
{
	int								size;
	unsigned int					seed;
	std::vector<std::vector<int>>	obstacle;

	size = (rand() % 6) + 1;
	std::cout << "size: " << size << std::endl;
	for (int i = 0 ; i < (3 + size * 2) ; i++)
	{
		std::vector<int>	tmp;
		for (int j = 0 ; j < (3 + size * 2)  ; j++)
		{
			if ((i == 0 || i == (3 + size * 2) - 1) && j != size + 1) // RANGEES
				tmp.push_back(1);
			else if ((j == 0 || j == (3 + size * 2) -1) && i != size + 1 ) // COLONNES
				tmp.push_back(1);
			else
				tmp.push_back(0);
		}
		obstacle.push_back(tmp);
	}
	return (obstacle);
}

std::vector<std::vector<int>>	Preset::type3(void) const
{
	int								size;
	unsigned int					seed;
	std::vector<std::vector<int>>	obstacle;

	size = (rand() % 5) + 1;
	std::cout << "size: " << size << std::endl;
	for (int i = 0 ; i < (5 + size * 2) ; i++)
	{
		std::vector<int>	tmp;
		for (int j = 0 ; j < (5 + size * 2)  ; j++)
		{
			if (i == size + 2 || j == size + 2)				// COLONNE + LIGNE CENTRALE
				tmp.push_back(1);
			else if (i != 0 && i != (5 + size * 2) - 1 && j != 0 && j != (5 + size * 2) - 1 // PAS SUR BORDURE
				&& i != size + 1 && i != size + 3 && j != size + 1 && j != size + 3) // MARGE INTERIEURE
				tmp.push_back(1);
			else
				tmp.push_back(0);
		}
		obstacle.push_back(tmp);
	}
	return (obstacle);
}
