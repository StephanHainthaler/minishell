# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 09:06:14 by shaintha          #+#    #+#              #
#    Updated: 2024/04/22 14:59:35 by shaintha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror #-g

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

clean:
	@rm -rf $(OBJ_DIR)
	@cd $(LIBFT_DIR) && make -s clean

fclean: clean
	@rm -rf $(NAME)
	@cd $(LIBFT_DIR) && make -s fclean

re: fclean all

.PHONY: all clean fclean re

