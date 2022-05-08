/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:59:05 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/08 17:04:58 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
#define SOLVER_H

#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_set>

#include "heuristics.h"
#include "node.h"

class Puzzle;

class Compare {
   public:
    bool operator()(Node* a, Node* b) {
        return (a->getMinTransitions() >= b->getMinTransitions());
    }
};

struct Hash {
    size_t operator()(const Node* node) const {
        size_t result = 0;
        const size_t max_size = node->getSizeFull();
        for (size_t i = 0; i < max_size; ++i) {
            result = node->data_[i] + (result * max_size);
        }
        // std::cout << "made hash:" << result << "\n";
        return (result);
    }
};

struct SetCompare {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return true;
        return 0 == std::memcmp(lhs->data_, rhs->data_, lhs->getSizeFull());
    }
};

class Solver {
   public:
    Solver(Puzzle& puzzle, heuristicFunction heuristic_);
    ~Solver();

    const heuristicFunction heuristic_;
    int solve();
    Node* getBestNode() const { return best_node_; }
    int getTimeComplexity() const { return time_complexity_; }
    int getSizeComplexity() const { return size_complexity_; }

   private:
    void tryAdd(const Node* n, enum operation op);
    void branch(const Node* n);
    void print();
    // std::function<bool(const Puzzle& a, const Puzzle& b)> *cmp;
    std::priority_queue<Node*, std::vector<Node*>, Compare> nodes_;
    std::unordered_set<const Node*, Hash, SetCompare> visited_;
    Node* best_node_ = nullptr;
    int time_complexity_ = 0;
    int size_complexity_ = 0;
};

#endif  // SOLVER_H
