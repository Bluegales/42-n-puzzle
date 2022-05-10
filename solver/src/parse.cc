/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:23:29 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/10 01:52:45 by pfuchs           ###   ########.fr       */
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
            std::cerr << "error in file " << e.what() << '\n';
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

void Parse::convertSnake() {
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
}

Parse::Parse(char *file_name) : order_(), snake_() {
    std::ifstream file;
    file.open(file_name);
    if (!file.is_open()) throw "Can't open file";
    std::string line;
    std::vector<uint8_t> numbers;
    while (std::getline(file, line))
        if (extractIntegers(line, numbers))
            throw "";
    if (std::size_t { 1u + numbers[0] * numbers[0] } != numbers.size())
        throw "Size mismatch";
    if (numbers.size() <= 5)
        throw "Too small";
    numbers.erase(numbers.begin());
    if (!areConsecutive(numbers)) throw "Non consecutive numbers";
    order_ = Puzzle(numbers);
    snake_ = Puzzle(numbers);
    convertSnake();
    file.close();
}

Parse::~Parse() {}
