/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:25:05 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/09 18:16:01 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

#include <iostream>

#include "heuristics.h"

typedef int (*priorityFunction)(const Node &);

Node::Node(const Node &node)
    : Puzzle(node),
      empty_id_(node.empty_id_),
      move_list_(node.move_list_),
      transitions_(node.transitions_),
      heuristic_(node.heuristic_) {}

Node::Node(const Node &node, enum operation op, heuristicFunction h)
    : Puzzle(node),
      empty_id_(node.empty_id_),
      move_list_(node.move_list_),
      transitions_(node.transitions_ + 1) {
    applyOperation(op);
    heuristic_ = h(*this);
    priority_ = heuristic_ + transitions_;
}

Node::Node(const Puzzle &puzzle, uint8_t empty, heuristicFunction h) : Puzzle(puzzle) {
    empty_id_ = empty;
    heuristic_ = h(*this);
    priority_ = heuristic_ + transitions_;
}

Node::~Node() {}

void Node::applyOperation(enum operation op) {
    uint8_t swap = 0;
    switch (op) {
        case kup:
            swap = empty_id_ - getSizeX();
            break;
        case kdown:
            swap = empty_id_ + getSizeX();
            break;
        case kleft:
            swap = empty_id_ - 1;
            break;
        case kright:
            swap = empty_id_ + 1;
            break;
    }
    std::swap(data_[empty_id_], data_[swap]);
    empty_id_ = swap;
    move_list_.push_back(op & 0b10);
    move_list_.push_back(op & 0b01);
}
