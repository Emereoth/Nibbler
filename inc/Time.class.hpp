/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Time.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 17:29:06 by acottier          #+#    #+#             */
/*   Updated: 2018/06/13 13:58:56 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H_
# define TIME_H_

# define MIN_FRAME_LEN 13

# include <time.h>
# include <unistd.h>

class Time
{
	public:
	        static void             calculDeltaTime( void );
	        static float    deltaTime( void );
	        static float    timeSinceLastUpdate( void );
	        static void             sleepAsMuchAsNeeded( void );
	        static float    _deltaTime;
	private:
	        Time( void );
	        Time( Time const & src );
	        ~Time( void );
	        Time &                  operator=( Time const & rhs );
	        static float    _lastClock;
};

#endif