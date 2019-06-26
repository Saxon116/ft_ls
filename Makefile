NAME = ft_ls

SRC = src/main.c src/shit.c src/parse.c src/display_l.c src/display.c src/recursive.c src/print.c src/print_l.c src/get_column.c src/flags_tu.c src/display_d.c src/nicolas.c

FLAGS = -Wextra -Wall -Werror -g

ifndef VERBOSE
.SILENT:
endif

all:$(NAME)

$(NAME): $(SRC)
	make -C libft
	gcc $(FLAGS) -o $(NAME) $(SRC) libft/libft.a
	echo "\033[32m$(NAME) compiled.\033[0m"

clean:
	make -C libft clean
	echo "\033[32mObjects files deleted.\033[0m"

fclean: clean
	make -C libft fclean
	rm -f ft_ls

re: fclean all
