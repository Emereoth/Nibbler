/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Preset.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:18:11 by acottier          #+#    #+#             */
/*   Updated: 2018/05/21 13:43:10 by acottier         ###   ########.fr       */
/*   Updated: 2018/05/19 18:32:06 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESET_HPP
# define PRESET_HPP

#include <vector>
#include <iostream>

class Preset
{
	public:
		
		Preset(void);
		~Preset(void);

		static std::vector<std::vector<int>>		type1(void);
		static std::vector<std::vector<int>>		type2(void);
		static std::vector<std::vector<int>>		type3(void);

	private:

		Preset(Preset const & src) = delete;
		Preset		&operator=(Preset const & rhs) = delete;

};

#endif
