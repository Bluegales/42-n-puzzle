/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:40:02 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/11 02:03:55 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "node.h"

/*
static int distance(uint8_t id, uint8_t value) {
        static
}
*/

int parity(const Puzzle &puzzle, uint8_t empty_id) {
    int size = puzzle.getSizeFull();
    int inversions = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int a = puzzle.get(i);
            int b = puzzle.get(j);
            if (i != empty_id && j != empty_id && a > b) inversions++;
        }
    }
    if (inversions < 6)
        return 0;
    std::cout << inversions << "\n";
    return inversions;
}

bool solvable(const Puzzle &puzzle, uint8_t empty_id) {
    int par = parity(puzzle, empty_id);
    if (puzzle.getSizeX() % 2 == 0) {
        int empty_x = puzzle.getSizeX() - empty_id / puzzle.getSizeX();
        par += empty_x + puzzle.getSizeX() / 2;
    }
    //std::cout << "parity:" << par << "\n";
    if (par % 2 == 0) {
        //std::cout << "# This puzzle is solvable\n";
        return true;
    }
    //std::cout << "# This puzzle is unsolvable\n";
    return false;
}

int manhattan(const Puzzle &puzzle, uint8_t empty_id) {
    int size = puzzle.getSizeX();
    int distance = 0;
    for (int y = 0; y < puzzle.getSizeX(); y++) {
        for (int x = 0; x < puzzle.getSizeX(); x++) {
            int id = puzzle.get(x, y);
            if (id != empty_id) {
                distance += abs(x - id % size) + abs(y - id / size);
            }
            // std::cout << "distance is: " << abs(x - correct.x) + abs(y -
            //  correct.y)
            //	<< " expected " << (int)puzzle.get(x, y) << " at: (" <<
            //(int)correct.x << "|" << (int)correct.y << ")" << std::endl;
        }
    }
    std::cout << "manhatten is: " << distance << std::endl;
    return distance;
}

int manhattan_weighted(const Puzzle &puzzle, uint8_t empty_id) {
    return ((manhattan(puzzle, empty_id) + 3 * misplaced(puzzle, empty_id)) / 3);
    int size = puzzle.getSizeX();
    int distance_combined = 0;
    for (int y = 0; y < puzzle.getSizeX(); y++) {
        for (int x = 0; x < puzzle.getSizeX(); x++) {
            int id = puzzle.get(x, y);
            if (id != empty_id) {
                // int min1 = std::max(size - x, x + 1);
                // int min2 = std::max(size - y, y + 1);
                int distance = abs(x - id % size) + abs(y - id / size);
                distance *= 1;
                distance_combined += distance;
            }
            // std::cout << "distance is: " << abs(x - correct.x) + abs(y -
            //  correct.y)
            //	<< " expected " << (int)puzzle.get(x, y) << " at: (" <<
            //(int)correct.x << "|" << (int)correct.y << ")" << std::endl;
        }
    }
    std::cout << "manhatten is: " << distance_combined << std::endl;
    return distance_combined;
}

int misplaced(const Puzzle &puzzle, uint8_t empty_id) {
    int size = puzzle.getSizeX();
    int distance = 0;
    for (int y = 0; y < puzzle.getSizeX(); y++) {
        for (int x = 0; x < puzzle.getSizeX(); x++) {
            int id = puzzle.get(x, y);
            if (id != empty_id) {
                if ((x - id % size) || (y - id / size))
                    distance++;
            }
        }
    }
    //std::cout << "misplaced is: " << distance << std::endl;
    return distance;
}
