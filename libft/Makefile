# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 20:03:57 by pvanderl          #+#    #+#              #
#    Updated: 2019/02/05 15:21:35 by pvanderl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

INCLUDES = ./includes/

SRCS = ./srcs/

FLAGS = -Wall -Wextra -Werror

FILES = atoi bzero isalnum isalpha isascii \
		isdigit isprint itoa lstadd lstdel \
		lstdelone lstiter lstmap lstnew memalloc \
		memccpy memchr memcmp memcpy memdel \
		memmove memset putchar putchar_fd putendl \
		putendl_fd putnbr putnbr_fd putstr putstr_fd \
		strcat strchr strclr strcmp strcpy \
		strdel strdup strequ striter striteri \
		strjoin strlcat strlen strmap strmapi \
		strncat strncmp strncpy strnequ strnew \
		strnstr strrchr strsplit strstr strsub \
		strtrim tolower toupper \
		lstiteri isspace min lstjoin

OFILES = get_next_line

OBJ = $(addprefix $(SRCS)ft_, $(addsuffix .o,$(FILES)))\
	  $(addprefix $(SRCS), $(addsuffix .o,$(OFILES)))

all: $(NAME)
		
$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "compilation \033[1;36mlibft\033[0;m finished"

$(OBJ): %.o:%.c
	@$(CC) $(FLAGS) -c -I $(INCLUDES) $^ -o $@

clean:
	@rm -rf $(OBJ)
	@echo "clean \033[1;31mlibft\033[0;m finished"

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean re fclean
