# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 12:13:51 by pfuchs            #+#    #+#              #
#    Updated: 2022/05/06 17:47:34 by pfuchs           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler Variables
CC		= g++
CFLAGSS	= -Wall -Wextra -Werror -Wno-shadow -std=c++17
INCFLAG	=
# File Variables
NAME	= test
FILES	= main
CLASSES	= parse
SRC		= $(addsuffix .cc,$(CLASSES) $(FILES))
HEADER	= $(addsuffix .h,$(CLASSES))
OBJ		= $(addprefix _bin/,$(notdir $(SRC:.cc=.o)))

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

_bin :
	mkdir _bin

_bin/%.o : %.cc | _bin
	$(CC) -c $(CFLAGSS) -MMD -MP $(INCFLAG) $< -o $@

clean:
	@rm -fr _bin

fclean:	clean
	@rm -f $(NAME)

re:		fclean all

all:	$(NAME)

.PHONY: clean fclean re all

-include $(OBJ:.o=.d)