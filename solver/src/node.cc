/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:25:05 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/08 16:46:57 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

#include <iostream>

Node::Node(const Node &node) : Puzzle(node) {
    moves_ = node.moves_;
    emptyField_ = node.emptyField_;
    transitions_ = node.transitions_;
    weight_ = node.weight_;
}

Node::Node(const Node &node, enum operation op, heuristicFunction f)
    : Puzzle(node) {
    moves_ = node.moves_;
    moves_.push_back(op & 0b10);
    moves_.push_back(op & 0b01);
    emptyField_ = applyOperation(op);
    transitions_ = node.transitions_ + 1;
    weight_ = f(*this);
}

Node::Node(const Puzzle &puzzle, heuristicFunction f) : Puzzle(puzzle) {
    transitions_ = 0;
    weight_ = f(puzzle);
    for (int i = 0; i < puzzle.getSizeFull(); i++) {
        if (puzzle.data_[i] == 0) emptyField_ = i;
    }
}

Node::~Node() {}

int Node::applyOperation(enum operation op) {
    uint8_t swap = 0;
    switch (op) {
        case kup:
            swap = emptyField_ - getSizeX();
            break;
        case kdown:
            swap = emptyField_ + getSizeX();
            break;
        case kleft:
            swap = emptyField_ - 1;
            break;
        case kright:
            swap = emptyField_ + 1;
            break;
    }
    // std::cout << "swapping: " << (int)emptyField_ << " with: " << (int)swap
    // << "\n";
    std::swap(data_[emptyField_], data_[swap]);
    return swap;
}
