# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabeloos <dabeloos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/05 17:21:38 by dabeloos          #+#    #+#              #
#    Updated: 2019/07/15 08:19:48 by pvanderl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# -g -fsanitize=address
# -Wno-unused-function

TEST_R		= resources/

TEST		= big1.txt

NAME		= lem-in

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -O3

CHEAD		= ./libft/includes

THISHEAD	= ./inc

MAIN_F		= main

READ_F		= start tools tools2

STRUCT_F	= array_1 array_2 btree room_1 room_2 global tube path ant

PRINT_F		= start

O_FILES		= $(addprefix ./src/, $(addsuffix .o,\
				$(MAIN_F) \
				$(addprefix read/, $(READ_F)) \
				$(addprefix structs/, $(STRUCT_F)) \
				$(addprefix print/, $(PRINT_F)) \
			))










#         !!!!!!!!!!!!!!!!!!! fclean libft















END_E		= \033[00m
RED_E		= \033[01;31m
GREEN_E		= \033[01;32m
YELLOW_E	= \033[01;33m
PURPLE_E	= \033[01;35m
CYAN_E		= \033[01;36m
WHITE_E		= \033[01;37m
BOLD_E		= \033[1m
UNDERLINE_E	= \033[4m

$(NAME):	$(O_FILES)
			@make -C libft/
			@gcc -o $(NAME) $(O_FILES) -L./libft/ -lft
			@echo "$(GREEN_E)end compilation$(END_E)"

all:		$(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) -c -o $@ $< -I$(THISHEAD) -I$(CHEAD) \
			-I$(THISHEAD)

clean:
			@rm -f $(O_FILES)
			@make -C libft/ clean
			@echo "$(PURPLE_E)end clean$(END_E)"

fclean:		clean
			@rm -f $(NAME)
			@make -C libft/ fclean
			@echo "$(RED_E)end fclean$(END_E)"

re:			clear fclean all

clear:
			@clear

norm:		clear
			@norminette $(addsuffix .c, $(basename $(O_FILES)))
			@norminette $(THISHEAD)/*

test:		fclean clear all
			./$(NAME) < $(TEST_R)$(TEST)


.PHONY: clean fclean all re
