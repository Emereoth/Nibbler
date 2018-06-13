/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathfinder.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:17:00 by acottier          #+#    #+#             */
/*   Updated: 2018/06/11 15:38:59 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHFINDER_HPP
# define PATHFINDER_HPP

#include "Snake.class.hpp"
#include <deque>

class Pathfinder
{
    public:

        Pathfinder(Map &map);
        ~Pathfinder();

        void                 spawnFood(Snake &snake);

        bool                 isReachable;

    private:

        explicit Pathfinder() = default;
        Pathfinder(Pathfinder & src) = default;
        Pathfinder          &operator=(Pathfinder & rhs) = default;

        void                run(int start);
        void                calculatePath(int start, std::deque<int> *path);
        bool                nextStep(int coordinate, std::deque<int> *path, int pathSize) const;
        bool                checkAvailability(int coordinate) const;

        Map                 &_map;
        int                 _food;
        int                 _start;
        int                 _sizeThreshold;
        int                 _snakeSize;
        std::deque<int>     _firstPath;
        std::deque<int>     _secondPath;

};

#endif