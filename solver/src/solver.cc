/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:57:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 19:32:49 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

#include <iostream>

#include "puzzle.h"
#include "heuristics.h"
#include "node.h"

Solver::Solver(Puzzle &puzzle, heuristicFunction f) : heuristic_(f)
{
	if (!solvable(puzzle))
	{
		std::cout << "not solvable\n";
		return;
	}
	nodes_.push(Node(puzzle, heuristic_));
}

Solver::~Solver()
{

}

int Solver::solve()
{
	if (nodes_.empty())
		return 0;
	while (1)
	{
		Puzzle top = nodes_.top();
		top.print();
		nodes_.pop();
		return 0;
	}
}
