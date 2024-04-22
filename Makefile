# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juitz <juitz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 09:06:14 by shaintha          #+#    #+#              #
#    Updated: 2024/04/22 15:31:38 by juitz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -fsanitize=leak #-g

SRC_DIR := sources
OBJ_DIR := objects
LIBFT_DIR := libft
MAIN_DIR := main

SRCS := $(SRC_DIR)/main.c

OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@cd $(LIBFT_DIR) && make -s
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)/libft.a -lreadline
	@LSAN_OPTIONS=suppressions=./lsan_suppress.txt ./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@cd $(LIBFT_DIR) && make -s clean

fclean: clean
	@rm -rf $(NAME)
	@cd $(LIBFT_DIR) && make -s fclean

re: fclean all

.PHONY: all clean fclean re

