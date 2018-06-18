/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathfinder.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:21:18 by acottier          #+#    #+#             */
/*   Updated: 2018/06/18 15:52:44 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pathfinder.class.hpp"
#include <vector>

#define MAP_SIZE 3844

Pathfinder::Pathfinder(Map &map) :isReachable(false), food(-1), _map(map), _sizeThreshold(15)
{
}

Pathfinder::~Pathfinder()
{
}

/*
*   Random location food spawner
*/
void				Pathfinder::spawnFood(Snake &snake)
{
	int			foodPos;

    _snakeSize = snake.size;
    if (food != -1)
        _map.map[food] = sprite::SOIL;
	while (!isReachable)
	{
		foodPos = (rand() % (61 * 61)) + 1;
		if (_map.map[foodPos] == sprite::SOIL)
            run(foodPos);
	}
    isReachable = false;
	_map.map[foodPos] = sprite::FOOD;
	food = foodPos;
	snake.eatFood = false;
}

/*
*   Runs the pathfinding twice and sets isReachable to true if given location is reachable
*/
void                Pathfinder::run(int start)
{
    calculatePath(start, &_firstPath);
    if (_firstPath.size() == 0)
        return ;
    calculatePath(start, &_secondPath);
    if (_secondPath.size() == 0)
        return ;
    
    isReachable = true;
    _firstPath.clear();
    _secondPath.clear();
}

/*
*   Creates array of path targets
*/
void                Pathfinder::createTargetArray(std::array<int, 4> &targets) const
{
    targets[DIR_RIGHT] = (_start + _sizeThreshold) / 62 == _start / 62 ? (_start + _sizeThreshold) : -1;
    targets[DIR_LEFT] = (_start - _sizeThreshold) / 62 == _start / 62 ? (_start - _sizeThreshold) : -1;
    targets[DIR_DOWN] = (_start + (_sizeThreshold * 62)) > 0 && (_start + (_sizeThreshold * 62)) < 62*62
                            ? (_start + (_sizeThreshold * 62)) : -1;
    targets[DIR_UP] = (_start - (_sizeThreshold * 62)) > 0 && (_start - (_sizeThreshold * 62)) < 62*62
                            ? (_start - (_sizeThreshold * 62)) : -1;

    return ;
}

/*
*   Calls recursive member function nextStep(), returns a fully valid path on success or an empty deque on fail 
*/
void                Pathfinder::calculatePath(int start, std::deque<int> *path)
{
    std::array<int, 4>      targets;

    _start = start;
    createTargetArray(targets);
    
    if (nextStep(start + 1, path, 0, targets) || nextStep(start - 1, path, 0, targets)
        || nextStep(start + 62, path, 0, targets) || nextStep(start - 62, path, 0, targets))
        return ;

    (*path).clear();
}

/*
*   Checks if target is a valid pixel
*/
bool                Pathfinder::checkTargetValidity(int target) const
{
    if (target != -1 && target <= MAP_SIZE && _map.map[target] == sprite::SOIL && target / 62 != 0 && target / 62 != 61 && target % 62 != 0 && target % 62 != 61)
        return (true);
    return (false);
}

/*
*   Checks differents paths until a valid one has been found (min distance: 15, or snakeSize if superior)
*/
bool                Pathfinder::nextStep(int coordinate, std::deque<int> *path, int pathSize, std::array<int, 4> &targets) const
{
    int                 x = coordinate % 62;
    int                 y = coordinate / 62;
    bool                validPath = false;

    if (targets[DIR_RIGHT] ==  -1 && targets[DIR_LEFT] == -1 && targets[DIR_DOWN] == -1 && targets[DIR_UP] == -1)       //
        return (false);                                                                                                 //
    if (coordinate < 0 || coordinate >= 62 * 62 ||                                                                      // Pixel availability checks
        (_map.map[coordinate] != sprite::SOIL && _map.map[coordinate] != sprite::PT_CIRCLE_GREEN)                       //
        || coordinate == _start || !checkAvailability(coordinate) )                                                     //
        return (false);                                                                                                 //
    
    if (targetReached(x, y, targets))
    {
        (*path).push_front(coordinate);
        return (true);
    }
    (*path).push_front(coordinate);

    std::multimap<int, int>              steps = createStepMap(coordinate, targets);
    std::multimap<int, int>::iterator    ii = steps.begin();

    while (!validPath && ii != steps.end())
    {
        validPath = nextStep((*ii).second, path, pathSize + 1, targets);
        ii++;
    }
    if (validPath)
        return (true);
    (*path).pop_front();
    return (false);
}

/*
*   Checks if path has reached one of the four targets
*/
bool                       Pathfinder::targetReached(int x, int y, std::array<int, 4> &targets) const
{
    if ((targets[DIR_LEFT] != -1 && x == targets[DIR_LEFT] % 62) || (targets[DIR_RIGHT] != -1 && x == targets[DIR_RIGHT] % 62)
         || (targets[DIR_DOWN] != -1 && y == targets[DIR_DOWN] / 62) || (targets[DIR_UP] != -1 && y == targets[DIR_UP] / 62))
        return (true);
    return (false);
}

/*
*   Create multimap classing different steps in order of efficiency
*/
std::multimap<int, int>  Pathfinder::createStepMap(int coordinate, std::array<int, 4> &targets) const
{
    std::multimap<int, int, std::less<int>>  res = 
    {
        {getStepValue(coordinate + 1, targets), coordinate + 1},
        {getStepValue(coordinate - 1, targets), coordinate - 1},
        {getStepValue(coordinate + 62, targets), coordinate + 62},
        {getStepValue(coordinate - 62, targets), coordinate - 62}
    };

    return (res);
}

/*
*   Returns heuristic value of given pixel relative to the target pixel (smaller value = closer)
*/
int                 Pathfinder::getStepValue(int coordinate, std::array<int, 4> &targets) const
{
    int             smallestDistance = INT_MAX;
    int             distance;
    int             i;
    int             closestTarget;

    for (i = 0 ; i < 4 ; i++)
    {
        if (targets[i] != -1)
        {
            if (i < 2)
                distance = std::abs(targets[i] % 62 - coordinate % 62);
            else
                distance = std::abs(targets[i] / 62 - coordinate / 62);
            if (distance < smallestDistance)
            {
                smallestDistance = distance;
                closestTarget = i;
            }
        }
    }
    return (smallestDistance);
}

/*
*   Checks if pixel is aready used in a path
*/
bool                Pathfinder::checkAvailability(int coordinate) const
{
    for (size_t i = 0 ; i < _firstPath.size() ; i++)
    {
        if (coordinate == _firstPath[i])
            return (false);
    }
    for (size_t i = 0 ; i < _secondPath.size() ; i++)
    {
        if (coordinate == _secondPath[i])
            return (false);
    }
    return (true);
}