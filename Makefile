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

READ_F		= legal_char_1 \
			  legal_char_2 \
			  read_1 \
			  read_2 \
			  read_ants \
			  read_command_1 \
			  read_command_2 \
			  read_room \
			  read_tube

STRUCTS_F	= global \
			  room_1 \
			  room_2 \
			  room_3 \
			  room_4 \
			  tube_1 \
			  tube_2 \
			  ant \
			  path \
			  paths

MAIN_F		= lemin

ALGO_F		= algo_1 \
			  algo_2 \
			  algo_3 \
			  bfs \
			  bmf \
			  check_roads_1 \
			  check_roads_2 \
			  cost

O_FILES		= $(addsuffix .o, \
			  	$(addprefix ./src/, \
				  	$(MAIN_F) \
				  	$(addprefix read/, $(READ_F)) \
					$(addprefix print/, $(PRINT_F)) \
					$(addprefix structs/, $(STRUCTS_F)) \
					$(addprefix algo/, $(ALGO_F))))

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
			@$(OSMAKE) -C libft/
			@$(CC) $(CFLAGS) -o $(NAME) $(O_FILES) -L./libft/ -lft
			@echo "$(GREEN_E)end compilation : $(NAME)$(END_E)"

all:		$(NAME)

small:		$(O_FILES)
			@$(CC) $(CFLAGS) -o $(NAME) $(O_FILES) -L./libft/ -lft
			@echo "$(GREEN_E)end compilation : $(NAME)$(END_E)"

%.o:		%.c
			@$(CC) $(CFLAGS) -c -o $@ $< -I$(LIBHEAD) -I$(THISHEAD)

sclean:
			@rm -f $(O_FILES)
			@echo "$(PURPLE_E)end clean : $(NAME)$(END_E)"

clean:		sclean
			@$(OSMAKE) -C libft/ clean

fclean:		sclean
			@rm -f $(NAME)
			@$(OSMAKE) -C libft/ fclean
			@echo "$(RED_E)end fclean : $(NAME)$(END_E)"

sfclean:	sclean
			@rm -f $(NAME)
			@echo "$(RED_E)end fclean : $(NAME)$(END_E)"

re:			fclean all

sre:		sfclean small

.PHONY: clean fclean all re small sclean sfclean sre
