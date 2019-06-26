# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 12:40:14 by dabeloos          #+#    #+#              #
#    Updated: 2019/03/05 18:44:00 by dabeloos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= gcc

CFLAGS		= #-Wall -Wextra -Werror

CHEAD		= ./includes

O_FILES		= ft_memset.o \
			  ft_bzero.o \
			  ft_memcpy.o \
			  ft_memccpy.o \
			  ft_memmove.o \
			  ft_memchr.o \
			  ft_memcmp.o \
			  ft_strlen.o \
			  ft_strdup.o \
			  ft_strcpy.o \
			  ft_strncpy.o \
			  ft_strcat.o \
			  ft_strncat.o \
			  ft_strlcat.o \
			  ft_strchr.o \
			  ft_strrchr.o \
			  ft_strstr.o \
			  ft_strnstr.o \
			  ft_strcmp.o \
			  ft_strncmp.o \
			  ft_atoi.o \
			  ft_atoi2.o \
			  ft_isalpha.o \
			  ft_isdigit.o \
			  ft_isalnum.o \
			  ft_isascii.o \
			  ft_isprint.o \
			  ft_toupper.o \
			  ft_tolower.o \
			  ft_memalloc.o \
			  ft_memdel.o \
			  ft_strnew.o \
			  ft_strdel.o \
			  ft_strclr.o \
			  ft_striter.o \
			  ft_striteri.o \
			  ft_strmap.o \
			  ft_strmapi.o \
			  ft_strequ.o \
			  ft_strnequ.o \
			  ft_strsub.o \
			  ft_strsub2.o \
			  ft_strjoin.o \
			  ft_strtrim.o \
			  ft_strsplit.o \
			  ft_itoa.o \
			  ft_itoa2.o \
			  ft_strrev.o \
			  ft_putchar.o \
			  ft_putstr.o \
			  ft_putendl.o \
			  ft_putnbr.o \
			  ft_putnbr2.o \
			  ft_putchar_fd.o \
			  ft_putstr_fd.o \
			  ft_putendl_fd.o \
			  ft_putnbr_fd.o \
			  ft_putnbr2_fd.o \
			  ft_lstnew.o \
			  ft_lstdelone.o \
			  ft_lstdel.o \
			  ft_lstdel_content.o \
			  ft_lstadd.o \
			  ft_lstiter.o \
			  ft_lstmap.o \
			  ft_swap_int.o \
			  ft_sort_int.o \
			  ft_array_strdel.o \
			  ft_index_of.o \
			  get_next_line.o

PRINTFHEAD	= ./ft_printf/includes

MAIN_F		= apply_ornament.o \
			  justify.o \
			  bases.o \
			  decode_format.o \
			  init_clean.o \
			  inspect_flags.o \
			  inspect_flags_support.o \
			  printf.o

HANDLERS_F	= handle_c.o \
			  handle_d.o \
			  handle_f.o \
			  handle_i.o \
			  handle_o.o \
			  handle_p.o \
			  handle_pctg.o \
			  handle_s.o \
			  handle_u.o \
			  handle_x.o \
			  handle_xmaj.o

FLOATS_F	= float_bits_extraction.o \
			  float_extraction.o \
			  float_extraction_support.o

CONVERS_F	= char_conversion.o \
			  float_bits_conversion.o \
			  float_conversion.o \
			  signed_conversion.o \
			  str_conversion.o \
			  unsigned_conversion.o

POLYADIC_F	= pf_boot.o \
			  pf_extrema.o \
			  pf_decimal_formatting.o \
			  pf_operations.o \
			  pf_manager.o \
			  pf_decimal_formatting_support.o \
			  pf_print_recursion.o \
			  pf_init_clean.o

PRINTF_F	= $(addprefix ./ft_printf/main/, $(MAIN_F)) \
			  $(addprefix ./ft_printf/handlers/, $(HANDLERS_F)) \
			  $(addprefix ./ft_printf/floats/, $(FLOATS_F)) \
			  $(addprefix ./ft_printf/conversions/, $(CONVERS_F)) \
			  $(addprefix ./ft_printf/polyadic_float/, $(POLYADIC_F))

END_E		= \033[00m
RED_E		= \033[01;31m
GREEN_E		= \033[01;32m
YELLOW_E	= \033[01;33m
PURPLE_E	= \033[01;35m
CYAN_E		= \033[01;36m
WHITE_E		= \033[01;37m
BOLD_E		= \033[1m
UNDERLINE_E	= \033[4m

$(NAME):	$(O_FILES) $(PRINTF_F)
			@ar -rcs $@ $^

all:		$(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) -c -o $@ $< -I$(CHEAD) -I$(PRINTFHEAD)

clean:
			@rm -f $(O_FILES)
			@rm -f $(PRINTF_F)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY: clean fclean all re
