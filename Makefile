# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabeloos <dabeloos@students.s19.be>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/05 17:21:38 by dabeloos          #+#    #+#              #
#    Updated: 2019/06/22 15:22:53 by pvanderl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# -g -fsanitize=address
# -Wno-unused-function

NAME		= lemin

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -O3

CHEAD		= ./libft/includes

THISHEAD	= ./inc

MAIN_F		= main

READ_F		= start tools

STRUCT_F	= array btree room global tube

O_FILES		= $(addprefix ./src/, $(addsuffix .o,\
				$(addprefix ./, $(MAIN_F)) \
				$(addprefix ./read/, $(READ_F)) \
			))

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

re:			fclean all

.PHONY: clean fclean all re
