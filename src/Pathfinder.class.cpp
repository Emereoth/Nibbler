/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathfinder.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:21:18 by acottier          #+#    #+#             */
/*   Updated: 2018/06/18 14:30:01 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pathfinder.class.hpp"
#include <vector>

#define MAP_SIZE 3844

Pathfinder::Pathfinder(AGraphics *window, Map &map, bool debug) :isReachable(false), food(-1), debug(debug), window(window), _map(map), _sizeThreshold(15)
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
    _map.map[start] = sprite::FOOD;
    calculatePath(start, &_firstPath);
    if (debug)
      std::cout << "Path ONE done" << std::endl;
    if (_firstPath.size() == 0)
    {
        if (debug)
            clearPathDebug(_firstPath);
        return ;
    }
    calculatePath(start, &_secondPath);
    if (debug)
        std::cout << "Path TWO done" << std::endl;
    if (_secondPath.size() == 0)
    {
        if (debug)
          clearPathDebug(_secondPath);
        return ;
    };
    
    if (debug)
        std::cout << "Two valid paths found, authorizing spawn" << std::endl;
    isReachable = true;
    clearPathDebug(_firstPath);
    clearPathDebug(_secondPath);
    _firstPath.clear();
    _secondPath.clear();
}

/*
*   Clears debug trace from path
*/
void                Pathfinder::clearPathDebug(std::deque<int> &path) const
{
    for (size_t i = 0 ; i < path.size() ; i++)
        _map.map[path[i]] = sprite::SOIL;
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

    if (debug)
        usleep(1000000);
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
    if (debug)
    {
      if (checkTargetValidity(targets[DIR_RIGHT]))
          _map.map[targets[DIR_RIGHT]] = sprite::PT_CIRCLE_GREEN;
      if (checkTargetValidity(targets[DIR_LEFT]))
          _map.map[targets[DIR_LEFT]] = sprite::PT_CIRCLE_GREEN;
      if (checkTargetValidity(targets[DIR_UP]))
          _map.map[targets[DIR_UP]] = sprite::PT_CIRCLE_GREEN;
      if (checkTargetValidity(targets[DIR_DOWN]))
          _map.map[targets[DIR_DOWN]] = sprite::PT_CIRCLE_GREEN;
        window->draw(_map);
        std::cout << "targets[DIR_RIGHT] : " << targets[DIR_RIGHT] << std::endl << "targets[DIR_LEFT] : " << targets[DIR_LEFT] <<
        std::endl << "targets[DIR_DOWN] : " << targets[DIR_DOWN] << std::endl << "targets[DIR_UP] : " << targets[DIR_UP] << std::endl;
    }
    if (nextStep(start + 1, path, 0, targets) || nextStep(start - 1, path, 0, targets)
        || nextStep(start + 62, path, 0, targets) || nextStep(start - 62, path, 0, targets))
    {
        if (debug)
        {
            if (targets[DIR_RIGHT] != -1)
                _map.map[targets[DIR_RIGHT]] = sprite::SOIL;
            if (targets[DIR_LEFT] != -1)
                _map.map[targets[DIR_LEFT]] = sprite::SOIL;
            if (targets[DIR_DOWN] != -1)
                _map.map[targets[DIR_DOWN]] = sprite::SOIL;
            if (targets[DIR_UP] != -1)
                _map.map[targets[DIR_UP]] = sprite::SOIL;
        }
        return ;
    }
    if (debug)
        std::cout << "no path available" << std::endl;
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

    if (targets[DIR_RIGHT] ==  -1 && targets[DIR_LEFT] == -1 && targets[DIR_DOWN] == -1 && targets[DIR_UP] == -1)
        return (false);
    if (coordinate < 0 || coordinate >= 62 * 62 ||
        (_map.map[coordinate] != sprite::SOIL && _map.map[coordinate] != sprite::PT_CIRCLE_GREEN)
        || coordinate == _start || !checkAvailability(coordinate) )
        return (false);
    
    if (targetReached(x, y, targets) && pathSize > _snakeSize)
    {
        (*path).push_front(coordinate);
        return (true);
    }

    (*path).push_front(coordinate);
    if (debug)
    {
        _map.map[coordinate] = sprite::PT_CIRCLE_GREEN;
        window->draw(_map);
    }

    std::multimap<int, int>              steps = createStepMap(coordinate, targets);
    std::multimap<int, int>::iterator    ii = steps.begin();
    int                                  i = 0;

    std::array<std::string, 4>          lol = {{"RIGHT", "LEFT", "DOWN", "UP"}};
    while (!validPath && ii != steps.end())
    {
        if (debug)
        {
            std::cout << "exploring next best step of score " << (*ii).first << "(#" << (*ii).second << ") : " << lol[i] << std::endl;
            usleep(1000000);
        }
        validPath = nextStep((*ii).second, path, pathSize + 1, targets);
        ii++;
        i++;
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
    if (debug)
    {
        std::cout << "Checking PATH_DONE conditions" << std::endl;
        std::cout << "Required x values: " << targets[DIR_LEFT] % 62 << " | " << targets[DIR_RIGHT] % 62 << std::endl;
        std::cout << "Required y values: " << targets[DIR_DOWN] / 62 << " | " << targets[DIR_UP] / 62 << std::endl;
        std::cout << "Current coord values: x -> " << x << " | y -> " << y << std::endl;
    }
    if ((targets[DIR_LEFT] != -1 && x == targets[DIR_LEFT] % 62) || (targets[DIR_RIGHT] != -1 && x == targets[DIR_RIGHT] % 62)
         || (targets[DIR_DOWN] != -1 && y == targets[DIR_DOWN] / 62) || (targets[DIR_UP] != -1 && y == targets[DIR_UP] / 62))
        return (true);
    return (false);
}

/*
*   Create maps classing different steps in order of efficiency
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
    std::array<std::string, 4>          lol = {{"RIGHT", "LEFT", "DOWN", "UP"}};

    if (debug)
        usleep(1000000);
    return (res);
}

/*
*   Returns heuristic value of given pixel relative to the target pixel (smaller value = closer)
*/
int                 Pathfinder::getStepValue(int coordinate, std::array<int, 4> &targets) const
{
    int             smallestDistance = INT_MAX;
    int             distance;
    std::array<std::string, 4>          lol = {{"RIGHT", "LEFT", "DOWN", "UP"}};
    int             i;
    int             closestTarget;

    std::cout << std::endl;
    std::cout << coordinate << std::endl;
    for (i = 0 ; i < 4 ; i++)
    {
        if (targets[i] != -1)
        {
            // std::cout << "Target " << lol[i] << ":" << std::endl;
            // if (i < 2)
            //     std::cout << "vertical distance: " << std::abs(targets[i] / 62 - coordinate / 62) << std::endl;
            // else
            //     std::cout << "horizontal distance: " << std::abs(targets[i] % 62 - coordinate % 62) << std::endl;
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
    // std::cout << "coordinate " << coordinate << " : registering new optimized target " << lol[closestTarget] << " with a distance score of " << smallestDistance << std::endl;
    return (smallestDistance);
    // if (xTarget != -1)
    //     return (std::abs(xTarget / 62 - coordinate / 62));
    // else
    //     return (std::abs(yTarget % 62 - coordinate % 62));
    // // return (xValue + yValue);
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