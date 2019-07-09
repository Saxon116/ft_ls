# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/13 12:50:22 by nkellum           #+#    #+#              #
#    Updated: 2019/04/25 13:44:42 by nkellum          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = flag_init_priority.c parse_flags.c print_arg.c print_double.c \
ft_printf.c print_hex.c undefined.c print_string.c print_octal.c \
print_num.c

SRC_PATH_AUX = ./libftprintf
SRC_AUX = ft_putchar.c ft_putstr.c ft_putnbr.c ft_strchr.c ft_strsub.c \
ft_isdigit.c ft_atoi.c ft_itoa_base.c ft_strlen.c ft_atoi_base.c \
ft_uputnbr.c ft_utoa_base.c contains.c num_length.c


OBJ = $(SRC:.c=.o)
OBJ_AUX = $(SRC_AUX:.c=.o)
OBJ += $(addprefix $(SRC_PATH_AUX)/,$(OBJ_AUX))

# This is a minimal set of ANSI/VT100 color codes
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m

# Colors
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m

all: $(NAME)

$(NAME): $(OBJ)
	#@gcc -Wall -Wextra -o $(NAME) $(OBJ) libftprintf/aux.a
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "${_CYAN}Compiled LibftPrintf${_END}"

%.o: %.c
	gcc -Wall -Wextra -I libftprintf/libftprintf.h -c $< -o $@

clean:
	@make -C libftprintf clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libftprintf fclean
	@rm -f $(NAME)

re: fclean all
