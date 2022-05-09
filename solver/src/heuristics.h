/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:27:02 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/09 17:54:19 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTICS
#define HEURISTICS

class Node;

typedef int (*heuristicFunction)(const Node &);

bool solvable(const Node &puzzle);
int manhattan(const Node &puzzle);
int misplaced(const Node &puzzle);

#endif // HEURISTICS
