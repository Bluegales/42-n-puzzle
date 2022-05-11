/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:20:38 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/10 20:46:07 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puzzle.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

uint8_t Puzzle::sizeX_;
uint8_t Puzzle::sizeFull_;

Puzzle::Puzzle() : data_(nullptr) {}

Puzzle::Puzzle(const std::vector<uint8_t>& data) {
    Puzzle::sizeFull_ = data.size();
    Puzzle::sizeX_ = sqrt(data.size());
    data_ = new u_int8_t[sizeFull_];
    std::copy(data.data(), data.data() + sizeFull_, data_);
}

Puzzle::Puzzle(const Puzzle& puzzle) {
    data_ = new u_int8_t[sizeFull_];
    std::copy(puzzle.data_, puzzle.data_ + sizeFull_, data_);
}

Puzzle::~Puzzle() { delete[] data_; }

Puzzle& Puzzle::operator=(Puzzle puzzle) {
    swap(*this, puzzle);
    return *this;
}

void Puzzle::print() const {
    for (int j = 0; j < sizeX_ + 1; j++) std::cout << "-----";
    std::cout << "\n";
    for (int i = 0; i < sizeFull_; i++) {
        std::cout << " |" << std::setw(3) << (int)data_[i];
        if ((i + 1) % sizeX_ == 0) {
            std::cout << " |\n";
            for (int j = 0; j < sizeX_; j++) std::cout << "------";
            std::cout << "\n";
        }
    }
}
