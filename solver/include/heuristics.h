/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:27:02 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/10 23:12:25 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "puzzle.h"

typedef int (*heuristicFunction)(const Puzzle &puzzle, uint8_t empty_id);

bool solvable(const Puzzle &puzzle, uint8_t empty_id);
int manhattan(const Puzzle &puzzle, uint8_t empty_id);
int manhattan_weighted(const Puzzle &puzzle, uint8_t empty_id);
int parity(const Puzzle &puzzle, uint8_t empty_id);
int misplaced(const Puzzle &puzzle, uint8_t empty_id);

#endif // HEURISTICS_H
