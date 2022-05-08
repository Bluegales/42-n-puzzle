/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:40:02 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/08 15:15:00 by pfuchs           ###   ########.fr       */
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

static int parity(const uint8_t *data, int size) {
    int inversions = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int a = data[i];
            int b = data[j];
            if (a && b && a > b) inversions++;
        }
    }
    return inversions;
}

bool solvable(const Puzzle &puzzle) {
    int par = parity(puzzle.data_, puzzle.getSizeFull());
    // std::cout << "parity is: " << par << "\n";
    if (puzzle.getSizeFull() % 2 == 0) {
        int test_empty_x = puzzle.emptyField_ / puzzle.getSizeX();
        int real_empty_x =
            solution().data[puzzle.getSizeX()][puzzle.getSizeFull() - 1].x;
        int offset = abs(test_empty_x - real_empty_x);
        par += offset;
    }
    if (par % 2 != 0) {
        return true;
    }
    return false;
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
            //  correct.y)
            //	<< " expected " << (int)puzzle.get(x, y) << " at: (" <<
            //(int)correct.x << "|" << (int)correct.y << ")" << std::endl;
        }
    }
    // std::cout << "manhatten is: " << distance << std::endl;
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
    //std::cout << "misplaced is: " << distance << std::endl;
    return distance;
}
