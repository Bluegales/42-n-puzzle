/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:20:38 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/06 13:22:16 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puzzle.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

inline uint8_t getX(uint8_t sizeX, uint8_t sizeY, uint8_t id) {

}

inline uint8_t getY(uint8_t sizeX, uint8_t sizeY, uint8_t id) {

}

Puzzle::Puzzle(std::vector<uint8_t> &data) {
    data_ = new u_int8_t[sizeFull_];
}

Puzzle::Puzzle(const Puzzle &oldPuzzle, enum operation op) {
    data_ = new u_int8_t[sizeFull_];
    if (!data_)
    {
        std::cerr << "error: ran out of memory :(\n";
        exit(0);
    }
    std::copy(oldPuzzle.data_, oldPuzzle.data_ + sizeX_ * sizeY_, data_);
}

Puzzle::~Puzzle()
{
    delete[] data_;
}

Position Puzzle::getEmptyField()
{
    for (int i = 0; i < sizeFull_; i++)
        if (data_[i] == sizeFull_) {
            return (Position){i / sizeX_, i % sizeY_};
        }
    std::cerr << "error: puzzle without an empty field\n";
    exit(0);
}

void Puzzle::applyOperation(enum operation op)
{
    Position empty = getEmptyField();
    Position swap = empty;
    switch(op)
    {
        case kup:
            swap.x--;
            if (swap.x < 0) return ;
        break;
        case kdown:
            swap.x++;
            if (swap.x == sizeX_) return ;
        break;
        case kleft:
            swap.y--;
            if (swap.y == 0) return ;
        break;
        case kright:
            swap.y++;
            if (swap.y == sizeY_) return ;
        break;
    }
    std::swap(data_[empty.x + empty.y * sizeY_],
              data_[swap.x + swap.y * sizeY_]);
}
