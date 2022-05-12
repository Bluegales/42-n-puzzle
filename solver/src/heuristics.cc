/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:40:02 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/13 00:04:52 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "node.h"

bool solvable(const Puzzle &puzzle, uint8_t empty_id) {
    int size = puzzle.getSizeFull();
    int inversions = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int a = puzzle.get(i);
            int b = puzzle.get(j);
            if (i != empty_id && j != empty_id && a > b) inversions++;
        }
    }
    int par = inversions;
    if (puzzle.getSizeX() % 2 == 0) {
        int empty_x = puzzle.getSizeX() - empty_id / puzzle.getSizeX();
        par += empty_x + puzzle.getSizeX() / 2;
    }
    if (par % 2 == 0) {
        return true;
    }
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
        }
    }
    return distance;
}

int parity(const Puzzle &puzzle, uint8_t empty_id) {
    int size = puzzle.getSizeFull();
    int inversions = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int a = puzzle.get(i);
            int b = puzzle.get(j);
            if (i != empty_id && a > b) inversions++;
        }
    }
    return inversions / (puzzle.getSizeX() - 1) + inversions % (puzzle.getSizeX() - 1);
}

int manhattan_weighted(const Puzzle &puzzle, uint8_t empty_id) {
    return ((manhattan(puzzle, empty_id) + 3 * misplaced(puzzle, empty_id)) / 3);
    int size = puzzle.getSizeX();
    int distance_combined = 0;
    for (int y = 0; y < puzzle.getSizeX(); y++) {
        for (int x = 0; x < puzzle.getSizeX(); x++) {
            int id = puzzle.get(x, y);
            if (id != empty_id) {
                int distance = abs(x - id % size) + abs(y - id / size);
                distance *= 1;
                distance_combined += distance;
            }
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
    return distance;
}
