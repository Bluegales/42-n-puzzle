/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:59:05 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 11:59:15 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER
#define SOLVER

#include <functional>
#include <queue>
#include <unordered_set>

#include "puzzle.h"

class Compare
{
public:
	bool operator() (Puzzle, Puzzle);
};

class Solver {
   public:
    Solver(Puzzle& puzzle);
    ~Solver();

    int solve();

   private:
   	Compare cmp;
    //std::function<bool(const Puzzle& a, const Puzzle& b)> *cmp;
    std::priority_queue<Puzzle, std::vector<Puzzle>, Compare> nodes_;
    //std::unordered_set<Puzzle> visited_;
};

#endif  // SOLVER
