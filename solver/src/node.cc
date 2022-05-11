/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:25:05 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/11 02:06:59 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

#include <iostream>

#include "heuristics.h"

typedef int (*priorityFunction)(const Node &);

static int calcPriority(uint16_t heuristic, uint16_t transitions, int weight) {
    if (weight == 0)
        return heuristic;
    if (weight >= 1000)
        return heuristic;
    return heuristic * (10 + weight) + transitions * 10;
}

Node::Node(const Node &node)
    : puzzle_(node.puzzle_),
      empty_id_(node.empty_id_),
      move_list_(node.move_list_),
      transitions_(node.transitions_),
      heuristic_(node.heuristic_),
      priority_(node.priority_) {}

Node::Node(const Node &node, Operation op, heuristicFunction h, int weight)
    : puzzle_(node.puzzle_),
      empty_id_(node.empty_id_),
      move_list_(node.move_list_),
      transitions_(node.transitions_ + 1),
      priority_(node.priority_) {
    applyOperation(op);
    heuristic_ = h(puzzle_, empty_id_);
    priority_ = calcPriority(heuristic_, transitions_, weight);
}

Node::Node(const Puzzle &puzzle, uint8_t empty, heuristicFunction h, int weight) : puzzle_(puzzle) {
    empty_id_ = empty;
    heuristic_ = h(puzzle_, empty_id_);
    priority_ = calcPriority(heuristic_, transitions_, weight);
}

Node::~Node() {}

void Node::applyOperation(Operation op) {
    uint8_t swap = 0;
    switch (op) {
        case Operation::kup:
            swap = empty_id_ - puzzle_.getSizeX();
            break;
        case Operation::kdown:
            swap = empty_id_ + puzzle_.getSizeX();
            break;
        case Operation::kleft:
            swap = empty_id_ - 1;
            break;
        case Operation::kright:
            swap = empty_id_ + 1;
            break;
    }
    puzzle_.swap_values(empty_id_, swap);
    empty_id_ = swap;
    move_list_.push_back((int)op & 0b10);
    move_list_.push_back((int)op & 0b01);
}
