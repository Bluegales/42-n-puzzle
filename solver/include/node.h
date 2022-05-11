/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:25:44 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/10 20:33:34 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
#define NODE_H

#include <functional>

#include "heuristics.h"
#include "puzzle.h"

enum struct Operation { kup = 0, kdown = 1, kleft = 2, kright = 3 };

class Node {
   public:
    Node(const Node &node);
    Node(const Node &node, Operation op, heuristicFunction f, int weight);
    Node(const Puzzle &puzzle, uint8_t empty, heuristicFunction f, int weight);
    ~Node();

    void applyOperation(Operation op);

    uint16_t getEmptyId() const { return empty_id_; }
    uint16_t getTransitions() const { return transitions_; }
    uint16_t getHeuristic() const { return heuristic_; }
    uint16_t getPriority() const { return priority_; }
    const std::vector<bool> getMoves() const { return move_list_; }

    Puzzle puzzle_;

   private:
    uint8_t empty_id_;
    std::vector<bool> move_list_;

    uint16_t transitions_ = 0;
    uint16_t heuristic_ = 0;
    int priority_ = 0;
};

#endif  // NODE_H
