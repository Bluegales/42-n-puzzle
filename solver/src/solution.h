/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:52:59 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/07 05:50:46 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLUTION
#define SOLUTION

#include <cstdint>

// generates snake case solutions
struct solution {
    constexpr solution() : data() {
        for (int n = 2; n <= 16; n++) {
            int border[4] = {1, n, n, 0};
            int i = 1;
            int x = -1;
            int y = 0;
            while (i <= n * n) {
                while (++x < border[1]) {
                    data[n][i].x = x;
                    data[n][i].y = y;
                    i++;
                }
                x--;
                border[1]--;
                while (++y < border[2]) {
                    data[n][i].x = x;
                    data[n][i].y = y;
                    i++;
                }
                y--;
                border[2]--;
                while (--x >= border[3]) {
                    data[n][i].x = x;
                    data[n][i].y = y;
                    i++;
                }
                x++;
                border[3]++;
                while (--y >= border[0]) {
                    data[n][i].x = x;
                    data[n][i].y = y;
                    i++;
                }
                y++;
                border[0]++;
            }
            data[n][0].x = data[n][n * n].x;
            data[n][0].y = data[n][n * n].y;
        }
    }
    struct s_data {
        uint8_t x;
        uint8_t y;
    } data[17][16 * 16 + 1];
};

const solution solutions = solution();

#endif  // SOLUTION
