# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yallo <yallo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 12:02:17 by yallo             #+#    #+#              #
#    Updated: 2023/11/27 12:03:22 by yallo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

CC = gcc
HEADER =
FLAGS = -Wall -Werror -Wextra

SRC_DIR = src/
OBJ_DIR = obj/

SRCS =
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) Makefile | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJS)
	rm -f $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	all

.PHONY: all clean fclean re
