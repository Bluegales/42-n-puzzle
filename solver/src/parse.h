/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:23:38 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/06 20:32:10 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE
#define PARSE

#include <vector>

int parse(char *file_name, std::vector<uint8_t> &numbers);

#endif // PARSE