NAME = ft_ls

SRC = main.c shit.c parse.c display_l.c recursive.c

FLAGS = -Wextra -Wall -Werror

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
