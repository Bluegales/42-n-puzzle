/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:57:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/08 20:31:07 by pfuchs           ###   ########.fr       */
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

int Solver::solve() {
    int best = INT32_MAX;
    if (nodes_.empty()) return 1;
    if (!solvable(*nodes_.top())) {
        std::cout << "not solvable\n";
        return 1;
    }
    while (!nodes_.empty()) {
        const Node *top = nodes_.top();
        nodes_.pop();
        if (best >= top->getMinTransitions()) {
            std::cout << "could be better:" << top->getMinTransitions();
            std::cout << " " << top->getTransitions() << "\n";
            //top->print();
            if (top->getWeight() == 0) {
                if (size_complexity_ < (int)nodes_.size()) size_complexity_ = nodes_.size();
                best = top->getTransitions();
                delete best_node_;
                best_node_ = new Node(*top);
                //return (0);
            } else {
                branch(top);
            }
        }
        //top->print();
        //std::cout << "popping\n";
        delete top;
        // print();
        // return 0;
    }
    return (0);
}

void Solver::tryAdd(const Node *n, enum operation op) {
    Node *temp = new Node(*n, op, heuristic_);
    if (!visited_.contains(temp)) {
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
