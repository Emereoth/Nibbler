/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Preset.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:18:11 by acottier          #+#    #+#             */
/*   Updated: 2018/05/24 12:29:21 by rvievill         ###   ########.fr       */
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

		Preset(Preset const & src) = default;
		Preset		&operator=(Preset const & rhs) = default;

};

#endif
