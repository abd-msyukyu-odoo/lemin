# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabeloos <dabeloos@students.s19.be>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/05 17:21:38 by dabeloos          #+#    #+#              #
#    Updated: 2019/06/22 12:23:03 by pvanderl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in

OSMAKE		:= 
ifeq ($(OS),Windows_NT)
	OSMAKE = mingw32-make.exe
else
	OSMAKE = make
endif

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -O3

LIBHEAD		= ./libft/includes

THISHEAD	= ./inc

PRINT_F		= lemin_error \
			  print

READ_F		= read

STRUCTS_F	= global \
			  room \
			  tube \
			  ant

MAIN_F		= test_lemin

ALGO_F		= algo bfs bmf check_roads cost

O_FILES		= $(addsuffix .o, \
			  	$(addprefix ./src/, \
				  	$(addprefix read/, $(READ_F)) \
					$(addprefix print/, $(PRINT_F)) \
					$(addprefix structs/, $(STRUCTS_F)) \
					$(addprefix algo/, $(ALGO_F))) \
				$(addprefix tests/, $(MAIN_F)))

END_E		= \033[00m
RED_E		= \033[01;31m
GREEN_E		= \033[01;32m
YELLOW_E	= \033[01;33m
PURPLE_E	= \033[01;35m
CYAN_E		= \033[01;36m
WHITE_E		= \033[01;37m
BOLD_E		= \033[1m
UNDERLINE_E	= \033[4m

#profiling -pg
#run executable compiled with g pg
#gprof executable.exe gmon.out > analysis.txt
$(NAME):	$(O_FILES)
			@$(OSMAKE) -C libft/
			@gcc -O3 -o $(NAME) $(O_FILES) -L./libft/ -lft
			@echo "$(GREEN_E)end compilation : $(NAME)$(END_E)"

all:		$(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) -c -o $@ $< -I$(LIBHEAD) -I$(THISHEAD)

lemclean:
			@rm -f $(O_FILES)
			@echo "$(PURPLE_E)end clean : $(NAME)$(END_E)"

clean:		lemclean
			@$(OSMAKE) -C libft/ clean

fclean:		lemclean
			@rm -f $(NAME)
			@$(OSMAKE) -C libft/ fclean
			@echo "$(RED_E)end fclean : $(NAME)$(END_E)"

re:			fclean all

.PHONY: clean fclean all re
