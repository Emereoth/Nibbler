/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathfinder.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:17:00 by acottier          #+#    #+#             */
/*   Updated: 2018/06/15 12:15:49 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHFINDER_HPP
# define PATHFINDER_HPP

#include "Snake.class.hpp"
#include <deque>

class Pathfinder
{
    public:

        Pathfinder(/*AGraphics *window, */Map &map);
        ~Pathfinder();

        void                 spawnFood(Snake &snake);

        bool                 isReachable;

    private:

        explicit Pathfinder() = default;
        Pathfinder(Pathfinder & src) = default;
        Pathfinder          &operator=(Pathfinder & rhs) = default;

        void                run(int start);
        void                calculatePath(int start, std::deque<int> *path);
        bool                checkTarget(int target) const;
        bool                nextStep(int coordinate, std::deque<int> *path, int pathSize, int xTarget, int yTarget) const;
        std::map<int, int>  createStepMap(int coordinate, int xTarget, int yTarget) const;
        int                 getStepValue(int coordinate, int xTarget, int yTarget) const;
        bool                checkAvailability(int coordinate) const;

        // AGraphics           *window;
        Map                 &_map;
        int                 _food;
        int                 _start;
        int                 _sizeThreshold;
        int                 _snakeSize;
        std::deque<int>     _firstPath;
        std::deque<int>     _secondPath;

};

#endif