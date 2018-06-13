/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Time.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 17:42:46 by acottier          #+#    #+#             */
/*   Updated: 2018/06/13 13:37:28 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../inc/Time.class.hpp"

float           Time::_lastClock = clock();
float           Time::_deltaTime;

// Calcul the time (in second) since the last call to this function
// We must call this before using deltaTime( void ), once by frame (call it at the begining of the game loop)
void            Time::calculDeltaTime( void ) {

        float cl = clock();

        _deltaTime = (float)(cl - _lastClock) / CLOCKS_PER_SEC;
        _lastClock = cl;
}

// Return _deltaTime
float           Time::deltaTime( void ) {

        return _deltaTime;
}

// Return time since last update
float           Time::timeSinceLastUpdate( void ) {

        float cl = clock();

        return (float)(cl - _lastClock) / CLOCKS_PER_SEC;
}

void            Time::sleepAsMuchAsNeeded( void ) {

        float last = timeSinceLastUpdate();

        std::cout << "last : " << last << " ||| MIN_FRAME_LEN : " << MIN_FRAME_LEN << std::endl;
        if (last < MIN_FRAME_LEN)
        {
                std::cout << "sleeping for " << (MIN_FRAME_LEN - last) * 1000 << std::endl;
                usleep((unsigned int)((MIN_FRAME_LEN - last) * 10000));
        }
        else
                std::cout << "No sleep duh" << std::endl;

}