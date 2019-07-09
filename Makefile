# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/02 14:59:03 by jmondino          #+#    #+#              #
#    Updated: 2019/07/09 16:10:09 by nkellum          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = src/acl.c src/add_new_entry.c src/column.c src/column_aux.c src/display.c src/fill_list.c src/free.c src/main.c src/offsets.c src/parsing.c src/parsing_aux.c src/print_color.c src/print_l.c src/print_l_aux.c src/recursive.c src/sort_list.c src/sort_list_aux.c src/sort_tab.c src/xattr.c src/add_new_entry_aux.c src/fill_list_aux.c

FLAGS = -Wextra -Wall -Werror

ifndef VERBOSE
.SILENT:
endif

all:$(NAME)

$(NAME): $(SRC)
	make -C libft
	make -C ft_printf
	gcc $(FLAGS) -o $(NAME) $(SRC) libft/libft.a ft_printf/libftprintf.a
	echo "\033[32m$(NAME) compiled.\033[0m"

clean:
	make -C libft clean
	make -C ft_printf clean
	echo "\033[32mObject files deleted.\033[0m"

fclean: clean
	make -C libft fclean
	make -C ft_printf fclean
	rm -f ft_ls

re: fclean all
