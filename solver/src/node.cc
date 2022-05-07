/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:25:05 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 19:33:15 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

Node::Node(Node &node, enum operation op, heuristicFunction f) : Puzzle(node){
	applyOperation(op);
	distance_ = node.distance_ + 1;
    weight_ = f(node);
}

Node::Node(Puzzle &puzzle, heuristicFunction f) : Puzzle(puzzle) {
	distance_ = 0;
    weight_ = f(puzzle);
}

Node::~Node() {
}

int Node::applyOperation(enum operation op)
{
    uint8_t swap;
    switch(op)
    {
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
    std::swap(data_[emptyField_], data_[swap]);
    return swap;
}