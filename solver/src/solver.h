/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:59:05 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 19:32:50 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER
#define SOLVER

#include <functional>
#include <queue>
#include <unordered_set>

#include "node.h"

class Puzzle;

typedef int (*heuristicFunction)(Puzzle &);

class Compare
{
public:
	bool operator() (Node a, Node b){
	    return (a.getWeight() <= b.getWeight());
    }
};

class Solver {
   public:
    Solver(Puzzle& puzzle, heuristicFunction heuristic_);
    ~Solver();

    const heuristicFunction heuristic_;
    int solve();

   private:
    //std::function<bool(const Puzzle& a, const Puzzle& b)> *cmp;
    std::priority_queue<Node, std::vector<Node>, Compare> nodes_;
    //std::unordered_set<Puzzle> visited_;
};

#endif  // SOLVER
