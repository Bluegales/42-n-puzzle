/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:23:38 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/09 21:23:48 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE
#define PARSE

#include <vector>

#include "puzzle.h"

class Parse {
   public:
    Parse(char *file_name);
    ~Parse();
    const Puzzle &getOrder() const { return order_; }
    const Puzzle &getSnake() const { return snake_; }
    uint8_t getSnakeEmpty() const { return snake_empty_; }

   private:
    void convertSnake();

    //bool isValid_;
    Puzzle order_;
    Puzzle snake_;
    uint8_t snake_empty_;
};

#endif  // PARSE
