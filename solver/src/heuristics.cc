/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:40:02 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 11:21:22 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "puzzle.h"
#include "solution.h"

/*
static int distance(uint8_t id, uint8_t value) {
        static
}
*/

bool solvable(const Puzzle &puzzle) {
    (void)puzzle;
    return true;
}

int manhattan(const Puzzle &puzzle) {
    int distance = 0;
    auto sol = solutions.data[puzzle.getSizeX()];
    for (int y = 0; y < puzzle.getSizeX(); y++) {
        for (int x = 0; x < puzzle.getSizeX(); x++) {
            int id = puzzle.get(x, y);
            if (id != 0) {
                auto correct = sol[puzzle.get(x, y)];
                if (puzzle.get(x, y) != 0)
                    distance += abs(x - correct.x) + abs(y - correct.y);
            }
            // std::cout << "distance is: " << abs(x - correct.x) + abs(y -
            // correct.y)
            //	<< " expected " << (int)puzzle.get(x, y) << " at: (" <<
            //(int)correct.x << "|" << (int)correct.y << ")" << std::endl;
        }
    }
    std::cout << "manhatten is: " << distance << std::endl;
    return distance;
}

int misplaced(const Puzzle &puzzle) {
    int distance = 0;
    auto sol = solutions.data[puzzle.getSizeX()];
    for (int y = 0; y < puzzle.getSizeX(); y++) {
        for (int x = 0; x < puzzle.getSizeX(); x++) {
            auto correct = sol[puzzle.get(x, y)];
            if (x - correct.x != 0 || y - correct.y != 0) distance++;
        }
    }
    std::cout << "misplaced is: " << distance << std::endl;
    return distance;
}
