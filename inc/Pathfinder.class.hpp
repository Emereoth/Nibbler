/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathfinder.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:17:00 by acottier          #+#    #+#             */
/*   Updated: 2018/06/06 17:22:26 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHFINDER_HPP
# define PATHFINDER_HPP

#include "Snake.class.hpp"
#include <deque>

class Pathfinder
{
    public:

        Pathfinder(Map &map, int snakeSize);
        ~Pathfinder();

        void            run(int start);

        bool            isReachable;

    private:

        explicit Pathfinder() = default;
        Pathfinder(Pathfinder & src) = default;
        Pathfinder      &operator=(Pathfinder & rhs) = default;

        std::deque<int>     calculatePath() const;
        bool                nextStep(int coordinate, std::deque<int> *path) const;
        bool                checkAvailability(int coordinate) const;

        Map                 &_map;
        int                 _sizeThreshold;
        int                 _start;
        std::deque<int>     _firstPath;
        std::deque<int>     _secondPath;
};

#endif