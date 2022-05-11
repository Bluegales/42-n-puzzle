/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:23:29 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/11 01:24:28 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "solution.h"



Parse::Parse(int argc, char **argv) : order_(), snake_() {
    if (argc < 2 || argc > 5) return;
    if (parsePuzzle(argv[1])) return;
    if (convertPuzzle()) return;
    if (argc >= 3)
        if (setHeuristic(argv[2])) return;
    if (argc >= 4)
        if (setWeight(argv[3])) return;
    if (argc >= 5)
        if (setOption(argv[4])) return;
    is_valid_ = true;
}

Parse::~Parse() {}

static int extractIntegers(std::string line, std::vector<uint8_t> &data) {
    std::istringstream lineData(line.substr(0, line.find_first_of('#')));
    std::string temp;
    while (!lineData.eof()) {
        lineData >> temp;
        if (temp.empty()) return 0;
        int n;
        try {
            n = std::stoi(temp);
        } catch (const std::exception &e) {
            return 1;
        }
        data.push_back(n);
        temp = "";
    }
    return 0;
}

static bool areConsecutive(std::vector<uint8_t> &numbers) {
    for (int i = 0; i < (int)numbers.size(); i++) {
        if (std::find(numbers.begin(), numbers.end(), i) == numbers.end())
            return false;
    }
    return true;
}

int Parse::parsePuzzle(char *filename)
{
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Cant open file\n";
        return 1;
    };
    std::string line;
    std::vector<uint8_t> numbers;
    while (std::getline(file, line)) {
        if (extractIntegers(line, numbers)) {
            std::cerr << "Error extracting integers\n";
            return 1;
        }
    }
    if (std::size_t { 1u + numbers[0] * numbers[0] } != numbers.size()) {
        std::cerr << "Size doesnt match\n";
        return 1;
    }
    if (numbers.size() <= 5) {
        std::cerr << "Solve it yourself...\n";
        return 1;
    }
    numbers.erase(numbers.begin());
    if (!areConsecutive(numbers)) {
        std::cerr << "Non consecutive numbers\n";
        return 1;
    }
    Puzzle asd(numbers);
    (void) asd;
    order_ = Puzzle(numbers);
    snake_ = Puzzle(numbers);
    file.close();
    return 0;
}

int Parse::convertPuzzle()
{
    int sizeX = order_.getSizeX();

    for (int i = 0; i < order_.getSizeFull(); i++) {
        auto convert = snake_solutions.data[sizeX][i];
        int convert_id = convert.x + convert.y * sizeX;
        for (int j = 0; j < order_.getSizeFull(); j++) {
            if (order_.get(j) == i) {
                if (i == 0) {
                    snake_empty_ = j;
                }
                snake_.set(j, convert_id);
            }
        }
    }
    return 0;
}

int Parse::setWeight(char *weight)
{
    try {
        weight_ = std::stoi(weight);
    } catch (const std::exception &e) {
        std::cerr << "error parsing weight\n";
        return 1;
    }
    if (weight_ < 0 || weight_ > 2000) {
        std::cerr << "weight not in range 0-2000\n";
        return 1;
    }
    return 0;
}

int Parse::setHeuristic(char *heuristic)
{
    int n;
    try {
        n = std::stoi(heuristic);
    } catch (const std::exception &e) {
        std::cerr << "error parsing heuristic\n";
        return 1;
    }
    if (n < 1 || n > 4) {
        std::cerr << "heuristic not in range 1-4\n";
        return 1;
    }
    switch (n)
    {
    case 1:
        heurisic_string_ = "manhattan";
        heurisic_ = manhattan;
        break;
    case 2:
        heurisic_string_ = "misplaced";
        heurisic_ = misplaced;
        break;
    case 3:
        heurisic_string_ = "parity";
        heurisic_ = parity;
        break;
    case 4:
        heurisic_string_ = "manhatten_weighted";
        heurisic_ = manhattan_weighted;
        break;
    }
    return 0;
}

int Parse::setOption(char *option)
{
    int n;
    try {
        n = std::stoi(option);
    } catch (const std::exception &e) {
        std::cerr << "error parsing option\n";
        return 1;
    }
    if (n < 0 || weight_ > 1) {
        std::cerr << "option not in range 0-1\n";
        return 1;
    }
    if (n == 0)
        return 0;
    option_ = Options::kcompare;
    option_string_ = "compare";
    return 0;
}