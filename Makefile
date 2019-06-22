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

PRINTFHEAD	= ./libft/ft_printf/includes

CHEAD		= ./libft

THISHEAD	= ./inc

MAIN_F		= main

READ_F		= 

O_FILES		= $(addsuffix .o,\
				$(addprefix ./main/, $(MAIN_F)) \
				$(addprefix ./read/, $(READ_F)) \
			)

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
			@$(CC) $(CFLAGS) -c -o $@ $< -I$(CHEAD) -I$(PRINTFHEAD) \
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
