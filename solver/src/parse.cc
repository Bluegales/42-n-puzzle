/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:23:29 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/06 21:43:29 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static int extractIntegers(std::string line, std::vector<uint8_t> &data) {
    std::istringstream lineData(line.substr(0, line.find_first_of('#')));
    std::string temp;
    while (!lineData.eof()) {
        lineData >> temp;
        if (temp.empty())
            return 0;
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

static bool areConsecutive(std::vector<uint8_t> &numbers)
{
    for (int i = 0; i < (int)numbers.size(); i++) {
        if(std::find(numbers.begin(), numbers.end(), i) == numbers.end())
            return false;
    }
    return true;
}

int parse(char *file_name, std::vector<uint8_t> &numbers) {
    std::ifstream file;
    file.open(file_name);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return (1);
    }
    std::string line;
    while (std::getline(file, line))
        if (extractIntegers(line, numbers)) return 1;
    if (numbers[0] * numbers[0] + 1 != (int)numbers.size())
    {
        std::cerr << "Size doesnt match\n";
        return (1);
    }
    numbers.erase(numbers.begin());
    if (!areConsecutive(numbers))
    {
        std::cerr << "Non consecutive numbers\n";
        return (1);
    }
    file.close();
    return 0;
}
