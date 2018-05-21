/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:17:24 by acottier          #+#    #+#             */
/*   Updated: 2018/05/21 15:23:58 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <array>
#include <map>
#include <list>

enum	 snakeOrientation
{
	UP = 1,
	DOWN,
	RIGHT,
	LEFT
};

enum	 snakeCombinedOrientation
{
	UP_LEFT = 5,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

typedef struct data
{
	std::array<int, 2>			pos;
	char						origin;
	char						destination;
	bool						head;
	bool						tail;
	bool						grow;
	std::map<char, std::string>	spriteMap = 
	{
		{ UP_LEFT , "upleft.png" },
		{ UP_RIGHT , "upright.png" },
		{ DOWN_LEFT , "downleft.png" },
		{ DOWN_RIGHT , "downright.png" }
	};
};

class Snake
{
	public:

		Snake();
		virtual ~Snake() = default;

		std::list<data &>	getSnake(void) const;
		void				grow(void);
		void				updatePos(void);

	private:
	
		Snake(const Snake &) = default;
		Snake &operator=(const Snake &) = default;


		std::list<data &>	_snake;
};

#endif // !SNAKE_HPP