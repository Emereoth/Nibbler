/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathfinder.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:21:18 by acottier          #+#    #+#             */
/*   Updated: 2018/06/06 17:22:39 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pathfinder.class.hpp"

Pathfinder::Pathfinder(Map &map, int snakeSize) : _map(map), _sizeThreshold(snakeSize > 15 ? snakeSize : 15)
{
}

Pathfinder::~Pathfinder()
{
}

void                Pathfinder::run(int start)
{
    isReachable = false;
    _start = start;
    
    _firstPath = calculatePath();
    if (_firstPath.size() == 0)
        return ;
    _secondPath = calculatePath();
    if (_secondPath.size() == 0)
        return ;
        
    isReachable = true;
    _firstPath.clear();
    _secondPath.clear();
}

std::deque<int>    Pathfinder::calculatePath() const
{
    std::deque<int>    res;

    if (!nextStep(_start, &res))
        res.clear();
    return (res);
}

bool                Pathfinder::nextStep(int coordinate, std::deque<int> *path) const
{
    int                 x = coordinate / 62;
    int                 y = coordinate % 62;
    bool                validPath = false;

    if (coordinate < 0 || coordinate >= 62 * 62 || _map.map[coordinate] != sprite::SOIL
        || ( _firstPath.size() == 0 && !checkAvailability(coordinate)) )
        return (false);
    if ( (x + _sizeThreshold > _start / 62 || x - _sizeThreshold <= _start / 62)
        && (y + _sizeThreshold >= _start % 62 || y - _sizeThreshold <= _start % 62) )
    {
        (*path).push_front(coordinate);
        return (true);
    }

    validPath = nextStep(coordinate + 1, path);
    if (!validPath)
        validPath = nextStep(coordinate - 1, path);
    if (!validPath)
        validPath = nextStep(coordinate + 62, path);
    if (!validPath)
        validPath = nextStep(coordinate - 62, path);
    if (validPath)
    {
        (*path).push_front(coordinate);
        return (true);
    }
    return (false);
}

bool                Pathfinder::checkAvailability(int coordinate) const
{
    for (size_t i = 0 ; i < _firstPath.size() ; i++)
    {
        if (coordinate == _firstPath[i])
            return (false);
    }
    return (true);
}