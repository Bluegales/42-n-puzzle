/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:26:28 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/06 13:21:24 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLE
#define PUZZLE

#include <cstdint>
#include <array>

enum operation { kup, kdown, kleft, kright };

struct Position {
    uint8_t x;
    uint8_t y;
};

class Puzzle
{

public:
    Puzzle(std::vector<uint8_t> &data);
    Puzzle(const Puzzle &oldPuzzle, enum operation op);
    ~Puzzle();

private:
    Position getEmptyField();
    void applyOperation(enum operation op);
    static uint8_t sizeX_;
    static uint8_t sizeY_;
    static uint8_t sizeFull_;
    uint8_t *data_;

private:
    /* data */
};

#endif // PUZZLE
