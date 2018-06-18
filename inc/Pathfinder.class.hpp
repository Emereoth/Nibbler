/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathfinder.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:17:00 by acottier          #+#    #+#             */
/*   Updated: 2018/06/18 15:51:00 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHFINDER_HPP
# define PATHFINDER_HPP

#include "Snake.class.hpp"
#include <deque>

enum targets
{
    DIR_RIGHT,
    DIR_LEFT,
    DIR_DOWN,
    DIR_UP
};

class Pathfinder
{
    public:

        Pathfinder(Map &map);
        ~Pathfinder();

        void                 spawnFood(Snake &snake);

        bool                isReachable;
        int                 food;

    private:

        explicit Pathfinder() = default;
        Pathfinder(Pathfinder & src) = default;
        Pathfinder          &operator=(Pathfinder & rhs) = default;

        void                    run(int start);
        void                    clearPathDebug(std::deque<int> &path) const;
        void                    createTargetArray(std::array<int, 4> &targets) const;
        void                    calculatePath(int start, std::deque<int> *path);
        bool                    checkTargetValidity(int target) const;
        bool                    nextStep(int coordinate, std::deque<int> *path, int pathSize, std::array<int, 4> &targets) const;
        bool                    targetReached(int x, int y, std::array<int, 4> &targets) const;
        std::multimap<int, int> createStepMap(int coordinate, std::array<int, 4> &targets) const;
        int                     getStepValue(int coordinate, std::array<int, 4> &targets) const;
        bool                    checkAvailability(int coordinate) const;

        Map                 &_map;
        int                 _start;
        int                 _sizeThreshold;
        int                 _snakeSize;
        std::deque<int>     _firstPath;
        std::deque<int>     _secondPath;

};

#endif