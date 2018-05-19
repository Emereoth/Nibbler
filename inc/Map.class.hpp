/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:50:15 by rvievill          #+#    #+#             */
/*   Updated: 2018/05/19 15:22:54 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

class Map {

	public:

		explicit Map(void);
		~Map(void);

		void				placeItem(void);
		void				displayMap(void) const;

		int					map[63][63];

	private:

		explicit 			Map(const Map &src);
		Map					&operator=(const Map &rhs);
		
		std::array<int, 2>	generateItem(int zoneStart[2], bool preset) const;
		void				generatePreset(void);
		void				generateRand(void);

		int					_obstacle[19][29];
};

#endif