# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmondino <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/02 14:59:03 by jmondino          #+#    #+#              #
#    Updated: 2019/07/02 15:01:24 by jmondino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ft_ls

SRC = src/acl.c src/add_new_entry.c src/column.c src/column_aux.c src/display.c src/fill_list.c src/free.c src/ft_ls.h src/libft.h src/main.c src/offsets.c src/parsing.c src/parsing_aux.c src/print_color.c src/print_l.c src/print_l_aux.c src/recursive.c src/sort_list.c src/sort_list_aux.c src/sort_tab.c src/xattr.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wextra -Wall -Werror

ifndef VERBOSE
.SILENT:
endif

all:$(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ)
	echo "\033[32m$(NAME) compiled.\033[0m"

clean:
	/bin/rm -f $(OBJ)
	echo "\033[32mAll .o have been erased.\033[0m"

fclean: clean
	/bin/rm -f $(NAME)
	echo "\033[32m$(NAME) erased.\033[0m"

re: fclean all

