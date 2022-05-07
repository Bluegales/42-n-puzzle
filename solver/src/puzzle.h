/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:26:28 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 18:50:40 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLE
#define PUZZLE

#include <cstdint>
#include <vector>

//enum operation { kup, kdown, kleft, kright };

class Puzzle {
   public:
    Puzzle(const std::vector<uint8_t> &data);
    Puzzle(const Puzzle &puzzle);
    ~Puzzle();

    void print();

    uint8_t get(uint8_t id) const { return data_[id]; }
    uint8_t get(uint8_t x, uint8_t y) const { return data_[x + y * sizeX_]; }
    uint8_t getSizeX() const { return sizeX_; }
    uint8_t getSizeFull() const { return sizeFull_; }

    uint8_t emptyField_;
    uint8_t *data_;
   private:
    static uint8_t sizeX_;
    static uint8_t sizeFull_;

};

#endif  // PUZZLE
