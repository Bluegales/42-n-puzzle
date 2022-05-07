/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:25:44 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 19:30:24 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE
#define NODE

#include "puzzle.h"
#include "heuristics.h"

#include <functional>

enum operation { kup, kdown, kleft, kright};

class Node : public Puzzle{
   public:
    Node(Node &node, enum operation op, heuristicFunction f);
    Node(Puzzle &puzzle, heuristicFunction f);
    ~Node();

    int applyOperation(enum operation op);

    uint16_t getWeight() const {return weight_;}
    void setWeight(uint16_t weight) {weight_ = weight;}
    uint16_t getDistance() const {return distance_;}

   private:
    uint16_t distance_;
    uint16_t weight_;
};

#endif  // NODE
