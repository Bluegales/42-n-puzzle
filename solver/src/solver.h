/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:59:05 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/10 04:11:48 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
#define SOLVER_H

#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_set>

#include "heuristics.h"
#include "node.h"

enum class SolveType { kbalanced = 0, kgreedy = 1 };

struct Hash {
    size_t operator()(const Puzzle* puzzle) const {
        size_t result = 0;
        const size_t max_size = puzzle->getSizeFull();
        for (size_t i = 0; i < max_size; ++i) {
            result = puzzle->get(i) + (result * max_size);
        }
        // std::cout << "made hash:" << result << "\n";
        return (result);
    }
};

struct SetCompare {
    bool operator()(const Puzzle* lhs, const Puzzle* rhs) const {
        if (0 ==
            std::memcmp(lhs->getData(), rhs->getData(), lhs->getSizeFull()))
            return true;
        //std::cout << "Hash failed\n";
        return false;
    }
};

class Priority {
   public:
    bool operator()(Node* a, Node* b) {
        if (a->getPriority() == b->getPriority())
            return (a->getTransitions() <= b->getTransitions());
        return (a->getPriority() > b->getPriority());
    }
};

class Solver {
   public:
    Solver(const Puzzle& puzzle, uint8_t empty, heuristicFunction heuristic);
    ~Solver();

    int solve(SolveType type);

    const heuristicFunction heuristic_;
    const Puzzle &start_;
    const int start_empty_;

    int Solver::solve(SolveType type);

    void print(int64_t duration);
    const Node* getBestNode() const { return best_node_; }
    int getTimeComplexity() const { return time_complexity_; }
    int getSizeComplexity() const { return size_complexity_; }

   private:
    int solveGreedy();
    int solveBalanced();
    void tryAdd(const Node* n, enum operation op);
    void branch(const Node* n);

    std::priority_queue<Node*, std::vector<Node*>, Priority> nodes_;
    std::unordered_set<const Puzzle*, Hash, SetCompare> visited_;

    // Solutions
    Node* best_node_ = nullptr;
    int time_complexity_ = 0;
    int size_complexity_ = 0;
};

#endif // SOLVER_H
