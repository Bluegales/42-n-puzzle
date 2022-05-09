/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:57:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/09 18:23:56 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

#include <chrono>
#include <iostream>

#include "heuristics.h"
#include "node.h"
#include "puzzle.h"

Solver::Solver(const Puzzle &puzzle, uint8_t empty, heuristicFunction f)
    : heuristic_(f) {
    Node *temp = new Node(puzzle, empty, heuristic_);
    nodes_.push(temp);
    visited_.insert(new Puzzle(puzzle));
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

int Solver::solve(SolveType type) {
    if (nodes_.empty()) return -1;
    if (!solvable(*nodes_.top())) {
        std::cout << "not solvable\n";
        return 1;
    }
    switch (type) {
        case SolveType::kgreedy:
            return (solveGreedy());
            break;
        case SolveType::kbalanced:
            return (solveBalanced());
            break;
        case SolveType::kperfect:
            return (solvePerfect());
        case SolveType::kcompare:
            solveGreedy();
            solveBalanced();
            break;
    }
    return 0;
}

int Solver::solveGreedy() {
    std::cout << "Greedy!\n";
    while (!nodes_.empty()) {
        const Node *top = nodes_.top();
        nodes_.pop();
        if (size_complexity_ < (int)nodes_.size())
            size_complexity_ = (int)nodes_.size();
        while (!nodes_.empty()) {
            auto temp = nodes_.top();
            nodes_.pop();
            visited_.insert(temp);
        }
        if (top->getHeuristic() == 0) {
            time_complexity_ = visited_.size() + nodes_.size();
            delete best_node_;
            best_node_ = new Node(*top);
        } else {
            // top->print();
            branch(top);
            if (nodes_.empty()) {
                std::cout << "Couldnt find an optimal solution...\n";
                time_complexity_ = visited_.size() + nodes_.size();
                best_node_ = new Node(*top);
            }
        }
        delete top;
    }

    return (0);
}

int Solver::solveBalanced() { return solvePerfect(); }

int Solver::solvePerfect() {
    while (!nodes_.empty()) {
        if (size_complexity_ < (int)nodes_.size())
            size_complexity_ = (int)nodes_.size();
        //std::cout << visited_.size() << "\n";
        const Node *top = nodes_.top();
        nodes_.pop();
        if (top->getHeuristic() == 0) {
            time_complexity_ = visited_.size();
            delete best_node_;
            best_node_ = new Node(*top);
            return 0;
        } else {
            branch(top);
        }
        delete top;
    }
    return (0);
}

void Solver::tryAdd(const Node *n, enum operation op) {
    Node *temp = new Node(*n, op, heuristic_);
    if (visited_.find(temp) == visited_.end()) {
        nodes_.push(temp);
        visited_.insert(new Puzzle(*temp));
    } else {
        delete temp;
    }
}

void Solver::branch(const Node *n) {
    int size = n->getSizeX();
    int empty = n->getEmptyId();
    // std::cout << size << empty << "\n";
    if (empty / size != 0) tryAdd(n, kup);
    if (empty / size != size - 1) tryAdd(n, kdown);
    if (empty % size != 0) tryAdd(n, kleft);
    if (empty % size != size - 1) tryAdd(n, kright);
}

void Solver::print() {
    for (int i = 0; i < (int)nodes_.size(); i++)
        while (!nodes_.empty()) {
            auto temp = nodes_.top();
            std::cout << "NODE:\n"
                      << "best: " << temp->getBestPossibleResult() << "\n";
            std::cout << "trans: " << temp->getTransitions() << "\n";
            std::cout << "heu: " << temp->getHeuristic() << "\n";
            std::cout << "prio " << temp->getPriority() << "\n";
            nodes_.pop();
            delete temp;
        }
}
