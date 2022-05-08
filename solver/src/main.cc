/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:22:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/08 19:48:09 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>
#include <iostream>
#include <vector>

#include "heuristics.h"
#include "parse.h"
#include "puzzle.h"
#include "solver.h"
#include "solution.h"

void print(const Puzzle &start, const Solver &solver, int64_t duration) {
    std::cout << "Took " << duration << "[µs]"
              << " (" << duration / 1000 << "ms)\n";
    auto solution = solver.getBestNode();
    //solution->print();
    std::cout << "Moves: " << solution->getTransitions() << "\n";
    std::cout << "Time complexity: " << solver.getTimeComplexity() << "\n";
    std::cout << "Size complexity: " << solver.getSizeComplexity() << "\n";
    std::cout << "http://localhost:8080/?nbr=";
    int size = start.getSizeX();
    Puzzle puzzle_convert(start);
    int hole = 0;
    for (int i = 0; i < size * size; i++) {
        auto convert = solutions.data[size][i];
        int convert_id = convert.x + convert.y * size;
        for (int j = 0; j < size * size; j++)
        {
            if (start.data_[j] == i)
            {
                if (i == 0)
                    hole = convert_id;
                puzzle_convert.data_[j] = convert_id;
            }
        }
    }
    for (int i = 0; i < size * size; i++){
        std::cout << (int)puzzle_convert.get(i);
        if (i != size * size - 1) {
            std::cout << ",";
        }
    }
    std::cout << "&hole=" << hole;
    std::cout << "&cmd=";
    auto moves = solution->getMoves();
    for (int i = 0; i < solution->getTransitions(); i++) {
        int op = (int)moves.at(i*2) * 2 + moves.at(i*2 + 1);
        std::cout << op;
    }
    std::cout << "\n";
    //std::cout << "logged moves: " << moves.size() << "\n";
}

int main(int argc, char **argv) {
    if (argc != 2) return (1);
    std::vector<uint8_t> numbers;
    if (parse(argv[1], numbers)) return (1);
    Puzzle puzzle(numbers);
    puzzle.print();
    std::chrono::steady_clock::time_point begin =
        std::chrono::steady_clock::now();
    Solver solver(puzzle, misplaced);
    if (solver.solve()) return 0;
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();
    print(puzzle, solver,
          std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
              .count());
    return 0;
}
