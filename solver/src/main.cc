/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:22:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 19:37:23 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "parse.h"
#include "puzzle.h"
#include "solver.h"
#include "heuristics.h"

int main(int argc, char **argv) {
    if (argc != 2)
        return (1);
    std::vector<uint8_t> numbers;
    if (parse(argv[1], numbers))
        return (1);
    Puzzle puzzle(numbers);
    Solver solver(puzzle, manhattan);
    solver.solve();
    return 0;
}
