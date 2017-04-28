# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/20 14:52:17 by gguiulfo          #+#    #+#              #
#    Updated: 2017/04/27 11:55:04 by gguiulfo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= ft_ls

CC			:= gcc
CFLAGS		+= -Wall -Wextra -Werror
CFLAGS		+= -I includes -I libft/includes
LDFLAGS		+= -L libft/ -lft
# LDFLAGS		+= alloc_wrap.c

LIBFT		:= libft/libft.a

FILES		:= ls_main ls_print ls_args

SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(SRC:.c=.o)

.PHONY = all clean fclean re

all: $(NAME)

$(LIBFT):
	@make -C libft

$(OBJ): %.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(LDFLAGS) -o $@ $^
	@echo "\033[32mCompiled Executable\033[0m"

clean:
	@rm -rf $(OBJ)
	@make -C libft clean
	@echo "\033[32mRemoved Object Files\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@echo "\033[32mRemoved Executable\033[0m"

re: fclean all


# test: $(TEST)
#
# stats: $(STATS)
#
# list: $(LIST)
#
# sort: $(SORT)
#
# recur: $(RECUR)
#
# $(TEST):
# 	@$(CC) $(CFLAGS) $(LDFLAGS) -o test test.c
#
# $(STATS):
# 	@$(CC) $(CFLAGS) $(LDFLAGS) -o stats stats.c
#
# $(LIST):
# 	@$(CC) $(CFLAGS) $(LDFLAGS) -o list list.c
#
# $(SORT):
# 	@$(CC) $(CFLAGS) $(LDFLAGS) -o sort sort.c
#
# $(RECUR)
# 	@$(CC) $(CFLAGS) $(LDFLAGS) -o recur recur.c
