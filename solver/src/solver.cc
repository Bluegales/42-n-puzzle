/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:57:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/10 22:08:10 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

#include <chrono>
#include <iostream>

#include "heuristics.h"
#include "node.h"
#include "puzzle.h"

Solver::Solver(const Puzzle &puzzle, uint8_t empty, heuristicFunction f, int weight)
    : heuristic_(f), start_(puzzle), start_empty_(empty), heuristic_weight_(weight) {
        reset();
}

Solver::~Solver() {
    for (auto i : visited_) {
        delete i;
    }
    while (!nodes_.empty()) {
        delete nodes_.top();
        nodes_.pop();
    }
}

void Solver::reset() {
    for (auto i : visited_) {
        delete i;
    }
    while (!nodes_.empty()) {
        delete nodes_.top();
        nodes_.pop();
    }
    nodes_.push(new Node(start_, start_empty_, heuristic_, heuristic_weight_));
    visited_.insert(new Puzzle(start_));
}

int Solver::solve() {
    reset();
    if (nodes_.empty()) return -1;
    if (!solvable(nodes_.top()->puzzle_, nodes_.top()->getEmptyId())) {
        std::cout << "not solvable\n";
        return 1;
    }
    if (heuristic_weight_ == 0) return solveGreedy();
    return solveBalanced();
}

int Solver::solveBalanced() {
    while (!nodes_.empty()) {
        if (size_complexity_ < (int)nodes_.size())
            size_complexity_ = (int)nodes_.size();
        const Node *top = nodes_.top();
        nodes_.pop();
        if (top->getHeuristic() == 0) {
            time_complexity_ = visited_.size();
            best_node_ = new Node(*top);
            return 0;
        } else {
            branch(top);
        }
        delete top;
    }
    return (0);
}

int Solver::solveGreedy() {
    while (!nodes_.empty()) {
        if (size_complexity_ < (int)nodes_.size())
            size_complexity_ = (int)nodes_.size();
        const Node *top = nodes_.top();
        nodes_.pop();
        while (!nodes_.empty()) {
            delete nodes_.top();
            nodes_.pop();
        }
        if (top->getHeuristic() == 0) {
            time_complexity_ = visited_.size();
            best_node_ = new Node(*top);
            return 0;
        } else {
            branch(top);
            if (nodes_.empty()) {
                std::cout << "Couldnt find an optimal solution...\n";
                time_complexity_ = visited_.size() + nodes_.size();
                best_node_ = new Node(*top);
            }
        }
        delete top;
    }
    return 0;
}

void Solver::tryAdd(const Node *n, Operation op) {
    Node *temp = new Node(*n, op, heuristic_, heuristic_weight_);
    if (visited_.find(&temp->puzzle_) == visited_.end()) {
        nodes_.push(temp);
        visited_.insert(new Puzzle(temp->puzzle_));
    } else {
        delete temp;
    }
}

void Solver::branch(const Node *n) {
    int size = n->puzzle_.getSizeX();
    int empty = n->getEmptyId();
    if (empty / size != 0) tryAdd(n, Operation::kup);
    if (empty / size != size - 1) tryAdd(n, Operation::kdown);
    if (empty % size != 0) tryAdd(n, Operation::kleft);
    if (empty % size != size - 1) tryAdd(n, Operation::kright);
}

void Solver::print(int64_t duration) {
    std::cout << "Took " << duration << "[µs]"
              << " (" << duration / 1000 << "ms)\n";
    std::cout << "Moves: " << best_node_->getTransitions() << "\n";
    std::cout << "Time complexity: " << getTimeComplexity() << "\n";
    std::cout << "Size complexity: " << getSizeComplexity() << "\n";
    std::cout << "https://bluegales.github.io/42-n-puzzle/?nbr=";
    for (int i = 0; i < start_.getSizeFull(); i++) {
        std::cout << int{start_.get(i)};
        if (i != start_.getSizeFull() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "&hole=" << start_empty_;
    std::cout << "&cmd=";
    auto moves = best_node_->getMoves();
    for (int i = 0; i < best_node_->getTransitions(); i++) {
        int op = int{moves.at(i * 2) * 2} + int{moves.at(i * 2 + 1)};
        std::cout << op;
    }
    std::cout << "\n";
}

// void Solver::print() {
//     for (int i = 0; i < (int)nodes_.size(); i++)
//         while (!nodes_.empty()) {
//             auto temp = nodes_.top();
//             std::cout << "NODE:\n"
//                       << "best: " << temp->getBestPossibleResult() << "\n";
//             std::cout << "trans: " << temp->getTransitions() << "\n";
//             std::cout << "heu: " << temp->getHeuristic() << "\n";
//             std::cout << "prio " << temp->getPriority() << "\n";
//             nodes_.pop();
//             delete temp;
//         }
// }