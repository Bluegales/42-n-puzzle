/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:23:29 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/06 18:33:43 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

std::vector<uint8_t> parse(char *file_name) {
    std::ifstream file;
    file.open (file_name);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        exit(0);
    }
    std::string line;
    std::cout << line << "\n";
    std::vector<uint8_t> numbers;
    while (std::getline(file, line))
    {
        std::istringstream lineData(line.substr( 0, line.find_first_of('#')));
        std::cout << "testing line:" << line << std::endl << std::flush;
        if (line.empty())
            continue;
        size_t pos;
        while (!line.empty()) {
            pos = line.find_first_not_of(' ');
            if (!line[pos])
                break;
            if (pos != std::string::npos)
            {
                int n;
                try
                {
                    n = std::stoi(line.substr(0, pos));
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                    exit(2) ;
                }
                numbers.push_back(n);
            }
            line.erase(0, pos + 1);
        }
    }
    file.close();
    return numbers;
}