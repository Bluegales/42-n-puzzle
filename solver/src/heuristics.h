/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:27:02 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 11:21:25 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTICS
#define HEURISTICS

#include "puzzle.h"

bool solvable(const Puzzle &puzzle);
int manhattan(const Puzzle &puzzle);
int misplaced(const Puzzle &puzzle);

#endif // HEURISTICS
