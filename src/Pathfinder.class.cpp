/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathfinder.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:21:18 by acottier          #+#    #+#             */
/*   Updated: 2018/06/12 14:14:28 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pathfinder.class.hpp"

Pathfinder::Pathfinder(Map &map) : isReachable(false), _map(map), _food(-1), _sizeThreshold(15)
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
		foodPos = (rand() % (62 * 62)) + 1;
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
    // std::cout << "calculating paths" << std::endl;
    calculatePath(start, &_firstPath);
    // std::cout << "Path ONE done" << std::endl;
    if (_firstPath.size() == 0)
        return ;
    calculatePath(start, &_secondPath);
    // std::cout << "Path TWO done" << std::endl;
    if (_secondPath.size() == 0)
        return ;
        
    // std::cout << "Two valid paths found, authorizing spawn" << std::endl;
    isReachable = true;
    _firstPath.clear();
    _secondPath.clear();
}

/*
*   Calls recursive member function nextStep(), returns a fully valid path on success or an empty deque on fail 
*/
void                Pathfinder::calculatePath(int start, std::deque<int> *path)
{
    _start = start;
    if (nextStep(start + 1, path, 0) || nextStep(start - 1, path, 0) || nextStep(start + 62, path, 0) || nextStep(start - 62, path, 0))
        return ;
    (*path).clear();
}

/*
*   Checks differents paths until a valid one has been found (min distance: 15, or snakeSize if superior)
*/
bool                Pathfinder::nextStep(int coordinate, std::deque<int> *path, int pathSize) const
{
    int                 x = coordinate / 62;
    int                 y = coordinate % 62;
    int                 startX = _start / 62;
    int                 startY = _start % 62;
    bool                validPath = false;

    if (coordinate < 0 || coordinate >= 62 * 62 || _map.map[coordinate] != sprite::SOIL
        || coordinate == _start || !checkAvailability(coordinate) )
    {
        // std::cout << "pixel availability check: failed" << std::endl;
        return (false);
    }
    if ( (x > startX + _sizeThreshold || x < startX - _sizeThreshold || y >= startY + _sizeThreshold || y <= startY - _sizeThreshold) 
        && pathSize > _snakeSize)
    {
        // std::cout << "path threshold reached, backtracking and adding pixels" << std::endl;
        (*path).push_front(coordinate);
        return (true);
    }

    (*path).push_front(coordinate);
    validPath = nextStep(coordinate + 1, path, pathSize + 1);
    if (!validPath)
        validPath = nextStep(coordinate - 1, path, pathSize + 1);
    if (!validPath)
        validPath = nextStep(coordinate + 62, path, pathSize + 1);
    if (!validPath)
        validPath = nextStep(coordinate - 62, path, pathSize + 1);
    if (validPath)
        return (true);
    // std::cout << "all possiblities failed, removing pixel from path" << std::endl;
    (*path).pop_front();
    return (false);
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