/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:40:02 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/09 23:32:23 by pfuchs           ###   ########.fr       */
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

static int parity(const Node &node) {
    int size = node.getSizeFull();
    int inversions = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int a = node.get(i);
            int b = node.get(j);
            if (i != node.getEmptyId() && j != node.getEmptyId() && a > b) inversions++;
        }
    }
    //std::cout << "empty is: " << node.getEmptyId() << "\n";
    return inversions;
}

bool solvable(const Node &node) {
    int par = parity(node);
    if (node.getSizeX() % 2 == 0) {
        int empty_x = node.getSizeX() - node.getEmptyId() / node.getSizeX();
        //std::cout << "empty is :" << empty_x << "\n";
        par += empty_x + node.getSizeX() / 2;
        //std::cout << "even:" << offset + 1 << "\n";
    }
    //std::cout << "parity:" << par << "\n";
    if (par % 2 == 0) {
        //std::cout << "# This puzzle is solvable\n";
        return true;
    }
    //std::cout << "# This puzzle is unsolvable\n";
    return false;
}

int manhattan(const Node &node) {
    int size = node.getSizeX();
    int distance = 0;
    for (int y = 0; y < node.getSizeX(); y++) {
        for (int x = 0; x < node.getSizeX(); x++) {
            int id = node.get(x, y);
            if (id != node.getEmptyId()) {
                distance += abs(x - id % size) + abs(y - id / size);
            }
            // std::cout << "distance is: " << abs(x - correct.x) + abs(y -
            //  correct.y)
            //	<< " expected " << (int)puzzle.get(x, y) << " at: (" <<
            //(int)correct.x << "|" << (int)correct.y << ")" << std::endl;
        }
    }
    //std::cout << "manhatten is: " << distance << std::endl;
    return distance;
}

int misplaced(const Node &puzzle) {
    int size = puzzle.getSizeX();
    int distance = 0;
    for (int y = 0; y < puzzle.getSizeX(); y++) {
        for (int x = 0; x < puzzle.getSizeX(); x++) {
            int id = puzzle.get(x, y);
            if (id != 0 && x - id % size != 0 && y - id / size) {
                distance++;
            }
        }
    }
    std::cout << "misplaced is: " << distance << std::endl;
    return distance;
}
