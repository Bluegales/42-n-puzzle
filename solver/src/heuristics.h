/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:27:02 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 19:26:35 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTICS
#define HEURISTICS

class Puzzle;

typedef int (*heuristicFunction)(Puzzle &);

bool solvable(const Puzzle &puzzle);
int manhattan(const Puzzle &puzzle);
int misplaced(const Puzzle &puzzle);

#endif // HEURISTICS
