NAME = ft_ls

SRC = main.c shit.c parse.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wextra -Wall -Werror

ifndef VERBOSE
.SILENT:
endif

all:$(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a
	echo "\033[32m$(NAME) compiled.\033[0m"

clean:
	/bin/rm -f $(OBJ)
	echo "\033[32mAll .o have been erased.\033[0m"

fclean: clean
	/bin/rm -f $(NAME)
	echo "\033[32m$(NAME) erased.\033[0m"

re: fclean all
