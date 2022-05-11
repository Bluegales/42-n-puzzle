/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:23:38 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/10 20:48:59 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include <string>

#include "puzzle.h"
#include "heuristics.h"

enum struct Options { kdefault = 0, kcompare = 1};

class Parse {
   public:
    Parse(int argc, char **argv);
    ~Parse();

    bool isValid() const { return is_valid_; }

    const Puzzle &getOrder() const { return order_; }
    const Puzzle &getSnake() const { return snake_; }
    uint8_t getSnakeEmpty() const { return snake_empty_; }
    uint16_t getWeight() const { return weight_; }
    heuristicFunction getHeuristicFunction() const { return heurisic_; }
    std::string getHeuristicString() const { return heurisic_string_; }
    Options getOption() const { return option_; }
    std::string getOptionString() const { return option_string_; }

   private:
    int parsePuzzle(char *filename);
    int convertPuzzle();
    int setWeight(char *weight);
    int setHeuristic(char *heuristic);
    int setOption(char *option);

    bool is_valid_ = false;
    Puzzle order_;
    Puzzle snake_;
    uint8_t snake_empty_;
    uint16_t weight_ = 1;
    heuristicFunction heurisic_ = manhattan;
    std::string heurisic_string_ = "manhattan";
    Options option_ = Options::kdefault;
    std::string option_string_ = "default";
};

#endif // PARSE_H
