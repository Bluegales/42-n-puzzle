/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:22:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/10 03:54:37 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>
#include <iostream>
#include <vector>

#include "heuristics.h"
#include "parse.h"
#include "puzzle.h"
#include "solution.h"
#include "solver.h"

using namespace std::chrono;

void print(const Puzzle &start, uint8_t empty,  const Solver &solver, int64_t duration) {
    std::cout << "Took " << duration << "[µs]"
              << " (" << duration / 1000 << "ms)\n";
    auto solution = solver.getBestNode();
    if (!solution) return;
    std::cout << "Moves: " << solution->getTransitions() << "\n";
    std::cout << "Time complexity: " << solver.getTimeComplexity() << "\n";
    std::cout << "Size complexity: " << solver.getSizeComplexity() << "\n";
    std::cout << "https://bluegales.github.io/42-n-puzzle/?nbr=";
    for (int i = 0; i < start.getSizeFull(); i++) {
        std::cout << int{start.get(i)};
        if (i != start.getSizeFull() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "&hole=" << int{empty};
    std::cout << "&cmd=";
    auto moves = solution->getMoves();
    for (int i = 0; i < solution->getTransitions(); i++) {
        int op = int{moves.at(i * 2) * 2} + int{moves.at(i * 2 + 1)};
        std::cout << op;
    }
    std::cout << "\n";
}

void setWeight(int argc, char **argv) {
    Node::heuristic_weight_ = 1;
    if (argc < 4)
        return;
    int n;
    try {
        n = std::stoi(argv[3]);
    } catch (const std::exception &e) {
        n = 1;
    }
    std::cout << "weight is: " << n << "\n";
    Node::heuristic_weight_ = n;
}

int getType(int argc, char **argv) {
    if (argc < 3)
        return 0;
    int n;
    try {
        n = std::stoi(argv[2]);
    } catch (const std::exception &e) {
        n = 0;
    }
    if (n < 0 || n > 3)
        n = 0;
    return n;
}

void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "n-puzzle file type weight\n";
    std::cout << "  type: 0 - default\n";
    std::cout << "  type: 1 - greedy\n";
    std::cout << "  type: 2 - compare\n";
    std::cout << "  type: 3 - default with different weights\n";
}

int solve() {
    int Solver::solve(SolveType type) {
    if (nodes_.empty()) return -1;
    if (!solvable(*nodes_.top())) {
        std::cout << "not solvable\n";
        return 1;
    }
    switch (type) {
        case SolveType::kbalanced:
            return (solveBalanced());
            break;
        case SolveType::kgreedy:
            return (solveGreedy());
            break;
        case SolveType::kcompare:
            solveGreedy();
            solveBalanced();
            break;
        case SolveType::kweights:
            solveGreedy();
            solveBalanced();
            break;
    }
    return 0;
}
}

int main(int argc, char **argv) {
    if (argc < 3 || argc > 4) {
        printUsage();
        return 1;
    }
    std::vector<uint8_t> numbers;
    Puzzle order;
    Puzzle snake;
    uint8_t snake_empty;
    try {
        Parse parse(argv[1]);
        order = parse.getOrder();
        snake = parse.getSnake();
        snake_empty = parse.getSnakeEmpty();
    } catch (const char *e) {
        std::cerr << e << '\n';
        return (1);
    }
    std::cout << "input:\n";
    order.print();
    setWeight(argc, argv);
    int type = getType(argc, argv);
    std::cerr << type << '\n';
    steady_clock::time_point begin = steady_clock::now();
    Solver solver(snake, snake_empty, manhattan);
    solver.solve((SolveType)type);
    steady_clock::time_point end = steady_clock::now();
    print(snake, snake_empty, solver, duration_cast<microseconds>(end - begin).count());
    return 0;
}
