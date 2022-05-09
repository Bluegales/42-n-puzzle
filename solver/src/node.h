/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:25:44 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/09 18:16:02 by pfuchs           ###   ########.fr       */
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
    Node(const Puzzle &puzzle, uint8_t empty, heuristicFunction f);
    ~Node();

    void applyOperation(enum operation op);

    uint16_t getHeuristic() const { return heuristic_; }
    uint16_t getEmptyId() const { return empty_id_; }
    uint16_t getTransitions() const { return transitions_; }
    uint16_t getPriority() const { return priority_; }
    uint16_t getBestPossibleResult() const { return heuristic_ + transitions_; }
    const std::vector<bool> getMoves() const { return move_list_; }

   private:
    uint8_t empty_id_;
    std::vector<bool> move_list_;
    const uint16_t transitions_ = 0;
    uint16_t heuristic_ = 0;
    uint16_t priority_ = 0;
};

#endif  // NODE_H
