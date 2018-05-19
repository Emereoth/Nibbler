/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Preset.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:18:11 by acottier          #+#    #+#             */
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
		// std::vector<std::vector<int>>	type2(void) const;
		// std::vector<std::vector<int>>	type3(void) const;
		// std::vector<std::vector<int>>	type4(void) const;
		// std::vector<std::vector<int>>	type5(void) const;

	private:

		Preset(Preset const & src) = delete;
		Preset		&operator=(Preset const & rhs) = delete;

};

#endif