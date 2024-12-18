# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 09:06:14 by shaintha          #+#    #+#              #
#    Updated: 2024/08/16 15:42:01 by shaintha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -g

SRC_DIR := sources
OBJ_DIR := objects
LIBFT_DIR := libft
MAIN_DIR := main

SRCS := $(SRC_DIR)/main.c \
$(SRC_DIR)/initialization.c \
$(SRC_DIR)/environment.c \
$(SRC_DIR)/lexer.c \
$(SRC_DIR)/lexer_utils.c \
$(SRC_DIR)/expansion.c \
$(SRC_DIR)/expansion_utils.c \
$(SRC_DIR)/quotation.c \
$(SRC_DIR)/parser.c \
$(SRC_DIR)/parser_utils.c \
$(SRC_DIR)/here_doc.c \
$(SRC_DIR)/executor.c \
$(SRC_DIR)/executor_utils.c \
$(SRC_DIR)/child.c \
$(SRC_DIR)/builtins_1.c \
$(SRC_DIR)/builtins_2.c \
$(SRC_DIR)/builtins_utils_1.c \
$(SRC_DIR)/builtins_utils_2.c \
$(SRC_DIR)/builtins_utils_3.c \
$(SRC_DIR)/signals.c \
$(SRC_DIR)/signal_handler.c \
$(SRC_DIR)/free.c

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

.PHONY: all clean fclean re val
