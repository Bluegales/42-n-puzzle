/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:25:44 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/08 16:42:21 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
#define NODE_H

#include <functional>

#include "heuristics.h"
#include "puzzle.h"

enum operation { kup, kdown, kleft, kright };

class Node : public Puzzle {
   public:
    Node(const Node &node);
    Node(const Node &node, enum operation op, heuristicFunction f);
    Node(const Puzzle &puzzle, heuristicFunction f);
    ~Node();

    // Node &operator=(const Node &a);

    int applyOperation(enum operation op);

    uint16_t getWeight() const { return weight_; }
    void setWeight(uint16_t weight) { weight_ = weight; }
    uint16_t getTransitions() const { return transitions_; }
    uint16_t getMinTransitions() const { return weight_ + transitions_; }
    std::vector<bool> getMoves() const { return moves_; }

   private:
    std::vector<bool> moves_;
    uint16_t transitions_ = 0;
    uint16_t weight_ = 0;
};

#endif  // NODE_H
