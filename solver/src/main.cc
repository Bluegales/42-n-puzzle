/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:22:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/09 17:54:57 by pfuchs           ###   ########.fr       */
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
    solution->print();
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
    // std::cout << "logged moves: " << moves.size() << "\n";
}

int main(int argc, char **argv) {
    if (argc != 3) return (1);
    std::vector<uint8_t> numbers;
    Puzzle order;
    Puzzle snake;
    uint8_t snake_empty;
    try {
        Parse parse(argv[1]);
        order = parse.getOrder();
        snake = parse.getSnake();
        snake_empty = parse.getSnakeEmpty();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return (1);
    }
    order.print();
    std::cout << "converted to\n";
    snake.print();
    int type = argv[2][0] - '0';
    if (type < 0 || type > 3) return 1;

    (void) snake;
    (void) order;
    steady_clock::time_point begin = steady_clock::now();
    Solver solver(snake, snake_empty, manhattan);
    solver.solve(SolveType::kperfect);
    steady_clock::time_point end = steady_clock::now();
    print(snake, snake_empty, solver, duration_cast<microseconds>(end - begin).count());
    return 0;
}
