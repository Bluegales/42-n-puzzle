/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:57:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/09 04:38:13 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

#include <iostream>
#include <chrono>

#include "heuristics.h"
#include "node.h"
#include "puzzle.h"

Solver::Solver(Puzzle &puzzle, heuristicFunction f) : heuristic_(f) {
    Node *temp = new Node(puzzle, heuristic_);
    nodes_.push(temp);
    visited_.insert(temp);
}

Solver::~Solver() {}

int Solver::solve(SolveType type, heuristicFunction f) {
    heuristic_ = f;
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

int Solver::solveGreedy()
{
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
            //top->print();
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

class BalancedCompare {
   public:
    bool operator()(Node* a, Node* b) {
        if (a->getBestPossibleResult() == b->getBestPossibleResult())
            return (a->getTransitions() < b->getTransitions());
        return (a->getBestPossibleResult() > b->getBestPossibleResult());
        int weightA = a->getBestPossibleResult() + a->getTransitions();
        int weightB = b->getBestPossibleResult() + b->getTransitions();
        return (weightA > weightB);
    }
};

int Solver::solveBalanced() {
    std::priority_queue<Node*, std::vector<Node*>, BalancedCompare> nodes;
    nodes.push(nodes_.top());
    nodes_.pop();
    std::cout << "balanced\n";
    auto tryAddB = [&nodes, this](const Node *n, enum operation op) {
        Node *temp = new Node(*n, op, heuristic_);
        if (visited_.find(temp) == visited_.end()) {
            nodes.push(temp);
        visited_.insert(temp);
        } else {
            delete temp;
        }
    };
    auto branchB = [&tryAddB](const Node *n) {
        int size = n->getSizeX();
        int empty = n->emptyField_;
        if (empty / size != 0) tryAddB(n, kup);
        if (empty / size != size - 1) tryAddB(n, kdown);
        if (empty % size != 0) tryAddB(n, kleft);
        if (empty % size != size - 1) tryAddB(n, kright);
    };
    while (!nodes.empty()) {
        if (size_complexity_ < (int)nodes.size())
            size_complexity_ = (int)nodes.size();
        std::cout << nodes.size() << "\n";
        const Node *top = nodes.top();
        nodes.pop();
        if (top->getHeuristic() == 0) {
            time_complexity_ = visited_.size() + nodes.size();
            delete best_node_;
            best_node_ = new Node(*top);
            return 0;
        } else {
            branchB(top);
        }
        delete top;
    }
    return (0);
}

int Solver::solvePerfect()
{
    while (!nodes_.empty()) {
        if (size_complexity_ < (int)nodes_.size())
            size_complexity_ = (int)nodes_.size();
        const Node *top = nodes_.top();
        nodes_.pop();
        if (top->getHeuristic() == 0) {
            time_complexity_ = visited_.size() + nodes_.size();
            delete best_node_;
            best_node_ = new Node(*top);
        } else {
            std::cout << "branching\n";
            branch(top);
            std::cout << "branching done\n";
        }
        delete top;
    }
    return (0);
}

void Solver::tryAdd(const Node *n, enum operation op) {
    Node *temp = new Node(*n, op, heuristic_);
    if (visited_.find(temp) == visited_.end()) {
        nodes_.push(temp);
        visited_.insert(temp);
    } else {
        delete temp;
    }
}

void Solver::branch(const Node *n) {
    int size = n->getSizeX();
    int empty = n->emptyField_;
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
            temp->print();
            nodes_.pop();
            delete temp;
        }
}
