/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:20:38 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/06 23:32:45 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puzzle.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>

uint8_t Puzzle::sizeX_;
uint8_t Puzzle::sizeFull_;

Puzzle::Puzzle(const std::vector<uint8_t> &data) {
    Puzzle::sizeFull_ = data.size();
    Puzzle::sizeX_ = sqrt(data.size());
    data_ = new u_int8_t[sizeFull_];
    std::copy(data.data(), data.data() + sizeFull_, data_);
    for (int i = 0; i < (int)data.size(); i++)
        if (data[i] == 0) emptyField_ = i;
}

Puzzle::Puzzle(const Puzzle &oldPuzzle, enum operation op) {
    data_ = new u_int8_t[sizeFull_];
    if (!data_)
    {
        std::cerr << "error: ran out of memory :(\n";
        exit(0);
    }
    std::copy(oldPuzzle.data_, oldPuzzle.data_ + sizeFull_, data_);
    emptyField_ = applyOperation(op);
}

Puzzle::~Puzzle()
{
    //delete[] data_;
}

void Puzzle::print()
{
    for (int j = 0; j < sizeX_ + 1; j++)
        std::cout << "-----";
    std::cout << "\n";
    for (int i = 0; i < sizeFull_; i++) {
        std::cout << " |" << std::setw(3) << (int)data_[i];
        if ((i + 1) % sizeX_ == 0)
        {
            std::cout << " |\n";
            for (int j = 0; j < sizeX_; j++)
                std::cout << "------";
            std::cout << "\n";
        }
    }
}

int Puzzle::applyOperation(enum operation op)
{
    uint8_t swap;
    switch(op)
    {
        case kup:
            swap = emptyField_ - sizeX_;
        break;
        case kdown:
            swap = emptyField_ + sizeX_;
        break;
        case kleft:
            swap = emptyField_ - 1;
        break;
        case kright:
            swap = emptyField_ + 1;
        break;
    }
    std::swap(data_[emptyField_], data_[swap]);
    return swap;
}
