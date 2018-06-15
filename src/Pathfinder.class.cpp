/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathfinder.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:21:18 by acottier          #+#    #+#             */
/*   Updated: 2018/06/15 12:03:33 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pathfinder.class.hpp"
#include <vector>

Pathfinder::Pathfinder(AGraphics *window, Map &map) :isReachable(false),  window(window), _map(map), _food(-1), _sizeThreshold(15)
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

    // std::cout << "spawning food" << std::endl;
    _snakeSize = snake.size;
    if (_food != -1)
        _map.map[_food] = sprite::SOIL;
	while (!isReachable)
	{
        // std::cout << "random placement loop" << std::endl;
		foodPos = (rand() % (61 * 61)) + 1;
		if (_map.map[foodPos] == sprite::SOIL)
            run(foodPos);
	}
    isReachable = false;
	_map.map[foodPos] = sprite::FOOD;
	_food = foodPos;
	snake.eatFood = false;
}

/*
*   Runs the pathfinding twice and sets isReachable to true if given location is reachable
*/
void                Pathfinder::run(int start)
{
    _map.map[start] = sprite::FOOD;
    calculatePath(start, &_firstPath);
    std::cout << "Path ONE done" << std::endl;
    // std::cin.ignore();
    if (_firstPath.size() == 0)
    {
        _map.map[start] = sprite::PT_CROSS;
        return ;
    }
    calculatePath(start, &_secondPath);
    // std::cin.ignore();
    std::cout << "Path TWO done" << std::endl;
    if (_secondPath.size() == 0)
    {
        _map.map[start] = sprite::PT_CROSS;
        return ;
    };
        
    std::cout << "Two valid paths found, authorizing spawn" << std::endl;
    isReachable = true;
    _firstPath.clear();
    _secondPath.clear();
}

/*
*   Calls recursive member function nextStep(), returns a fully valid path on success or an empty deque on fail 
*/
void                Pathfinder::calculatePath(int start, std::deque<int> *path)
{
    int     rightTarget = ((start + _sizeThreshold) / 62 == start / 62 ? start + _sizeThreshold : -1);
    int     leftTarget = ((start - _sizeThreshold) / 62 == start / 62 ? start - _sizeThreshold : -1);
    int     upTarget = ((start - _sizeThreshold * 62) % 62 == start % 62 ? start - _sizeThreshold * 62 : -1);
    int     downTarget = ((start + _sizeThreshold * 62) % 62 == start % 62 ? start + _sizeThreshold * 62 : -1);

    _start = start;
    if (rightTarget != -1 && checkTarget(rightTarget))
        _map.map[rightTarget] = sprite::PT_CIRCLE_GREEN;
    if (leftTarget != -1 && checkTarget(leftTarget))
        _map.map[leftTarget] = sprite::PT_CIRCLE_GREEN;
    if (upTarget != -1 && checkTarget(upTarget))
        _map.map[upTarget] = sprite::PT_CIRCLE_GREEN;
    if (downTarget != -1 && checkTarget(downTarget))
        _map.map[downTarget] = sprite::PT_CIRCLE_GREEN;
    window->draw(_map);
    std::cout << "rightTarget : " << rightTarget << std::endl << "leftTarget : " << leftTarget <<
        std::endl << "downTarget : " << downTarget << std::endl << "upTarget : " << upTarget << std::endl;
    usleep(800000);
    if (nextStep(start + 1, path, 0, -1, rightTarget) || nextStep(start - 1, path, 0, -1, leftTarget)
        || nextStep(start + 62, path, 0, downTarget, -1) || nextStep(start - 62, path, 0, upTarget, -1))
        return ;
    std::cout << "no path available" << std::endl;
    for (size_t i = 0 ; i < (*path).size() ; i++)
        _map.map[(*path)[i]] = sprite::PT_CIRCLE;
    (*path).clear();
}

/*
*   Checks if target is a valid pixel
*/
bool                Pathfinder::checkTarget(int target) const
{
    if (target != -1 && _map.map[target] == sprite::SOIL)
        return (true);
    return (false);
}

/*
*   Checks differents paths until a valid one has been found (min distance: 15, or snakeSize if superior)
*/
bool                Pathfinder::nextStep(int coordinate, std::deque<int> *path, int pathSize, int xTarget, int yTarget) const
{
    int                 x = coordinate / 62;
    int                 y = coordinate % 62;
    // int                 startX = _start / 62;
    // int                 startY = _start % 62;
    bool                validPath = false;
    std::vector<int>    deadEnds;

    std::cout << std::endl << std::endl << std::endl;
    // std::cout << "testing #" << coordinate << "(" << x << ", " << y << ")" << std::endl;
    // std::cout << "xTarget " << xTarget / 62 << " ,yTarget " << yTarget % 62 << std::endl; 
    if (xTarget == -1 && yTarget == -1)
    {
        // std::cout << "Invalid target." << std::endl;
        return (false);
    }
    if (coordinate < 0 || coordinate >= 62 * 62 ||
        (_map.map[coordinate] != sprite::SOIL && _map.map[coordinate] != sprite::PT_CIRCLE_GREEN)
        || coordinate == _start || !checkAvailability(coordinate) )
    {
        std::cout << "pixel #" << coordinate << " availability check: failed" << std::endl;
        return (false);
    }
    std::cout << "availability OK" << std::endl;
    if ((x == xTarget / 62 || y == yTarget  % 62) && pathSize > _snakeSize)
    // if ( (x > startX + _sizeThreshold || x < startX - _sizeThreshold || y >= startY + _sizeThreshold || y <= startY - _sizeThreshold) 
    //     && pathSize > _snakeSize)
    {
        std::cout << "path threshold reached, backtracking and adding pixels" << std::endl;
        (*path).push_front(coordinate);
        return (true);
    }

    std::cout << "#" << coordinate << " added to current path" << std::endl;
    (*path).push_front(coordinate);
    _map.map[coordinate] = sprite::PT_CIRCLE_GREEN;
    window->draw(_map);

    std::map<int, int>              steps = createStepMap(coordinate, xTarget, yTarget);
    std::map<int, int>::iterator    ii = steps.begin();

    while (!validPath && ii != steps.end())
    {
        usleep(500000);
        std::cout << "exploring next best step of score " << (*ii).first << "(#" << (*ii).second << ")" << std::endl;
        validPath = nextStep((*ii).second, path, pathSize + 1, xTarget, yTarget);
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
    std::cout << "all possiblities failed, removing pixel #" << coordinate << " from path" << std::endl;
    (*path).pop_front();
    _map.map[coordinate] = sprite::PT_CIRCLE;
    return (false);
}

/*
*   Create maps classing different steps in order of efficiency
*/
std::map<int, int>  Pathfinder::createStepMap(int coordinate, int xTarget, int yTarget) const
{
    std::map<int, int, std::less<int>>  res = 
    {
        {getStepValue(coordinate + 1, xTarget, yTarget), coordinate + 1},
        {getStepValue(coordinate - 1, xTarget, yTarget), coordinate - 1},
        {getStepValue(coordinate + 62, xTarget, yTarget), coordinate + 62},
        {getStepValue(coordinate - 62, xTarget, yTarget), coordinate - 62}
    };

    return (res);
}

/*
*   Returns heuristic value of given pixel relative to the target pixel (smaller value = closer)
*/
int                 Pathfinder::getStepValue(int coordinate, int xTarget, int yTarget) const
{
    // int     xValue = std::abs((target / 62) - (coordinate / 62));
    // int     yValue = std::abs((target % 62) - (coordinate % 62));

    if (xTarget != -1)
        return (std::abs(xTarget / 62 - coordinate / 62));
    else
        return (std::abs(yTarget % 62 - coordinate % 62));
    // return (xValue + yValue);
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