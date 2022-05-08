/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:20:38 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/08 09:19:32 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puzzle.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>
#include <cstring>

uint8_t Puzzle::sizeX_;
uint8_t Puzzle::sizeFull_;

Puzzle::Puzzle(const std::vector<uint8_t> &data) {
    //std::cerr << "puz alive data\n";
    Puzzle::sizeFull_ = data.size();
    Puzzle::sizeX_ = sqrt(data.size());
    data_ = new u_int8_t[sizeFull_];
    std::copy(data.data(), data.data() + sizeFull_, data_);
    emptyField_ = 42;
    for (int i = 0; i < (int)data.size(); i++)
        if (data[i] == 0) emptyField_ = i;
    //std::cerr << "Empty is:" << (int)emptyField_ << "\n";
}

Puzzle::Puzzle(const Puzzle &puzzle)
{
    //std::cerr << "puz alive ref\n";
    data_ = new u_int8_t[sizeFull_];
    if (!data_)
    {
        std::cerr << "error: ran out of memory :(\n";
        exit(0);
    }
    std::copy(puzzle.data_, puzzle.data_ + sizeFull_, data_);
    emptyField_ = puzzle.emptyField_;
}

Puzzle::~Puzzle()
{
    //std::cerr << "puz dead :(\n";
    delete[] data_;
}

void Puzzle::print() const
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
