/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:25:44 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 12:05:06 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE
#define NODE

#include "puzzle.h"

class Node : Puzzle{
   public:
    Node(Puzzle puzzle);
    ~Node();

   private:
    Puzzle puzzle_;
};

#endif  // NODE