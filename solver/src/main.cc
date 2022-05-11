/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:22:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/11 01:24:34 by pfuchs           ###   ########.fr       */
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

void printResult(const Solver &solver, int64_t duration) {
    std::cout << "Took " << duration << "[µs]"
              << " (" << duration / 1000 << "ms)\n";
    auto solution = solver.getBestNode();
    if (!solution) return;
    std::cout << "Moves: " << solution->getTransitions() << "\n";
    std::cout << "Time complexity: " << solver.getTimeComplexity() << "\n";
    std::cout << "Size complexity: " << solver.getSizeComplexity() << "\n";
    std::cout << "https://bluegales.github.io/42-n-puzzle/?nbr=";
    for (int i = 0; i < solver.start_.getSizeFull(); i++) {
        std::cout << int{solver.start_.get(i)};
        if (i != solver.start_.getSizeFull() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "&hole=" << int{solver.start_empty_};
    std::cout << "&cmd=";
    auto moves = solution->getMoves();
    for (int i = 0; i < solution->getTransitions(); i++) {
        int op = int{moves.at(i * 2) * 2} + int{moves.at(i * 2 + 1)};
        std::cout << op;
    }
    std::cout << "\n";
}

void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "n-puzzle file heuristic weight option\n";
    std::cout << "  heuristic:\n";
    std::cout << "    0 - manhattan (default)\n";
    std::cout << "    1 - misplaced\n";
    std::cout << "    2 - parity\n";
    std::cout << "  weight: (default 1)\n";
    std::cout << "    0  = greedy\n";
    std::cout << "    1-2000 how more important are the steps to goal than the steps already traveled:\n";
    std::cout << "    1  = find optimal solution (dont try on size bigger 4)\n";
    std::cout << "    2000 = find solution very fast\n";
    std::cout << "  option:\n";
    std::cout << "    0 - none (default)\n";
    std::cout << "    1 - compare multiple weights (ignores weight)\n";
}

void printInput(Parse &parse) {
    std::cout << "input puzzle:\n";
    parse.getOrder().print();
    std::cout << "heuristic:" << parse.getHeuristicString() << "\n";
    std::cout << "weight:" << parse.getWeight() << "\n";
    std::cout << "option:" << parse.getOptionString() << "\n";
    std::cout << "starting....\n";
}

int main(int argc, char **argv) {
    Parse parse(argc, argv);
    if (!parse.isValid()) {
        printUsage();
        return 1;
    }
    printInput(parse);
    steady_clock::time_point begin = steady_clock::now();
    Solver solver(parse.getSnake(), parse.getSnakeEmpty(), parse.getHeuristicFunction(), parse.getWeight());
    solver.solve();
    steady_clock::time_point end = steady_clock::now();
    printResult(solver, duration_cast<microseconds>(end - begin).count());
    return 0;
}
