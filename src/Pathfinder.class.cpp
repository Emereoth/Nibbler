/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathfinder.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:21:18 by acottier          #+#    #+#             */
/*   Updated: 2018/06/16 12:24:34 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pathfinder.class.hpp"
#include <vector>

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
	int			foodPos = -1;

	if (debug)
    	std::cout << "spawning food" << std::endl;
    _snakeSize = snake.size;
    if (food != -1)
        _map.map[food] = sprite::SOIL;
	while (!isReachable)
	{
		if (foodPos != -1)
			_map.map[foodPos] = sprite::SOIL;
		if (debug)
        	std::cout << "random placement loop" << std::endl;
		foodPos = (rand() % (61 * 61)) + 1;
		if (_map.map[foodPos] == sprite::SOIL)
            run(foodPos);
	}
    isReachable = false;
	_map.map[foodPos] = sprite::FOOD;
	food = foodPos;
	snake.eatFood = false;
	if (debug)
    	std::cout << "food spawned" << std::endl;
	clearPathDebug(_firstPath);
	clearPathDebug(_secondPath);
}

/*
*   Runs the pathfinding twice and sets isReachable to true if given location is reachable
*/
void                Pathfinder::run(int start)
{
	if (debug)
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
    // targets[DIR_DOWN] = (_start + _sizeThreshold) * 62 % 62 == _start % 62 ? (_start + _sizeThreshold) * 62 / 62 : -1;
    // targets[DIR_UP] = (_start - _sizeThreshold) * 62 % 62 == _start % 62 ? (_start - _sizeThreshold) * 62 / 62 : -1;
    targets[DIR_DOWN] = (_start + (_sizeThreshold * 62)) > 0 && (_start + (_sizeThreshold * 62)) < 62*62
                            ? (_start + (_sizeThreshold * 62)) : -1;
    targets[DIR_UP] = (_start - (_sizeThreshold * 62)) > 0 && (_start - (_sizeThreshold * 62)) < 62*62
                            ? (_start - (_sizeThreshold * 62)) : -1;

	if (debug)
	{
		std::cout << "start" << _start << std::endl;
		usleep(1000000);
	}
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
      if (checkTarget(targets[DIR_RIGHT]))
          _map.map[targets[DIR_RIGHT]] = sprite::PT_CIRCLE_GREEN;
      if (checkTarget(targets[DIR_LEFT]))
          _map.map[targets[DIR_LEFT]] = sprite::PT_CIRCLE_GREEN;
      if (checkTarget(targets[DIR_UP]))
          _map.map[targets[DIR_UP]] = sprite::PT_CIRCLE_GREEN;
      if (checkTarget(targets[DIR_DOWN]))
          _map.map[targets[DIR_DOWN]] = sprite::PT_CIRCLE_GREEN;
        window->draw(_map);
    std::cout << "targets[DIR_RIGHT] : " << targets[DIR_RIGHT] << std::endl << "targets[DIR_LEFT] : " << targets[DIR_LEFT] <<
        std::endl << "targets[DIR_DOWN] : " << targets[DIR_DOWN] << std::endl << "targets[DIR_UP] : " << targets[DIR_UP] << std::endl;
    usleep(800000);
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
bool                Pathfinder::checkTarget(int target) const
{
    if (target != -1 && target <= 62 * 62 && _map.map[target] == sprite::SOIL)
        return (true);
    return (false);
}

/*
*   Checks differents paths until a valid one has been found (min distance: 15, or snakeSize if superior)
*/
bool                Pathfinder::nextStep(int coordinate, std::deque<int> *path, int pathSize, std::array<int, 4> &targets) const
{
    int                 x = coordinate / 62;
    int                 y = coordinate % 62;
    // int                 startX = _start / 62;
    // int                 startY = _start % 62;
    bool                validPath = false;

    // std::cout << "testing #" << coordinate << "(" << x << ", " << y << ")" << std::endl;
    // std::cout << "xTarget " << xTarget / 62 << " ,yTarget " << yTarget % 62 << std::endl; 
    if (targets[DIR_RIGHT] ==  -1 && targets[DIR_LEFT] == -1 && targets[DIR_DOWN] == -1 && targets[DIR_UP] == -1)
    {
        // std::cout << "Invalid target." << std::endl;
        return (false);
    }
    if (coordinate < 0 || coordinate >= 62 * 62 ||
        (_map.map[coordinate] != sprite::SOIL && _map.map[coordinate] != sprite::PT_CIRCLE_GREEN)
        || coordinate == _start || !checkAvailability(coordinate) )
    {
        // std::cout << "pixel #" << coordinate << " availability check: failed" << std::endl;
        return (false);
    }
    // std::cout << "availability OK" << std::endl;
    if ((x == targets[DIR_LEFT] / 62 || x == targets[DIR_RIGHT] / 62 || y == targets[DIR_DOWN] % 62 || y == targets[DIR_UP] % 62)
        && pathSize > _snakeSize)
    // if ( (x > startX + _sizeThreshold || x < startX - _sizeThreshold || y >= startY + _sizeThreshold || y <= startY - _sizeThreshold) 
    //     && pathSize > _snakeSize)
    {
        // std::cout << "path threshold reached, backtracking and adding pixels" << std::endl;
        (*path).push_front(coordinate);
        return (true);
    }

    (*path).push_front(coordinate);
    if (debug)
    {
        // std::cout << "#" << coordinate << " added to current path" << std::endl;
        _map.map[coordinate] = sprite::PT_CIRCLE_GREEN;
        window->draw(_map);
    }

    std::map<int, int>              steps = createStepMap(coordinate, targets);
    std::map<int, int>::iterator    ii = steps.begin();

    while (!validPath && ii != steps.end())
    {
        if (debug)
		{
            usleep(1000000);
        	std::cout << "exploring next best step of score " << (*ii).first << "(#" << (*ii).second << ")" << std::endl;
		}
        validPath = nextStep((*ii).second, path, pathSize + 1, targets);
        ii++;
    }
    if (validPath)
        return (true)
;
    // validPath = nextStep(coordinate + 1, path, pathSize + 1, target);
    // if (!validPath)
    //     validPath = nextStep(coordinate - 1, path, pathSize + 1, target);
    // if (!validPath)
    //     validPath = nextStep(coordinate + 62, path, pathSize + 1, target);
    // if (!validPath)
    //     validPath = nextStep(coordinate - 62, path, pathSize + 1, target);
    // if (validPath)
    //     return (true);
    // std::cout << "all possiblities failed, removing pixel #" << coordinate << " from path" << std::endl;
    (*path).pop_front();
    // if (debug)
    //     _map.map[coordinate] = sprite::PT_CIRCLE;
    return (false);
}

/*
*   Create maps classing different steps in order of efficiency
*/
std::map<int, int>  Pathfinder::createStepMap(int coordinate, std::array<int, 4> &targets) const
{
    std::map<int, int, std::less<int>>  res = 
    {
        {getStepValue(coordinate + 1, targets), coordinate + 1},
        {getStepValue(coordinate - 1, targets), coordinate - 1},
        {getStepValue(coordinate + 62, targets), coordinate + 62},
        {getStepValue(coordinate - 62, targets), coordinate - 62}
    };
    int                                 i = 0;
    int                                 smallStep = INT_MAX;
    int                                 currentTarget = -1;

    for (std::map<int, int>::iterator ii = res.begin() ; ii != res.end() ; ii++)
    {
        if (smallStep > (*ii).first)
        {
            smallStep = (*ii).first;
            currentTarget =i;
        }
        i++;
    }
	if (debug)
    	std::cout << "current target: " << i << std::endl;
    return (res);
}

/*
*   Returns heuristic value of given pixel relative to the target pixel (smaller value = closer)
*/
int                 Pathfinder::getStepValue(int coordinate, std::array<int, 4> &targets) const
{
    // int     xValue = std::abs((target / 62) - (coordinate / 62));
    // int     yValue = std::abs((target % 62) - (coordinate % 62));
    int             smallestDistance = INT_MAX;
    int             distance;

    for (int i = 0 ; i < 4 ; i++)
    {
        if (targets[i] != -1)
        {
            distance = std::abs((targets[i] / 62) - (coordinate / 62)) + std::abs((targets[i] % 62) - (coordinate % 62));
            if (distance < smallestDistance)
                smallestDistance = distance;
        }
    }
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