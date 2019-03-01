NAME = ./ft_ssl
HEADER = ./ft_ssl.h
LIB = ./libft/libft.a
FLAGS = -Werror -Wextra -Wall -g
SRC = ${wildcard *.c}

SRCO = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRCO) $(HEADER)
	@make -C libft
	gcc $(SRCO) $(LIB) -o $(NAME)

%.o: %.c
	@gcc -c $(FLAGS) $< -o $@

clean:
	@/bin/rm -f $(SRCO)
	@/bin/rm -f compile_commands.json
	@/bin/rm -rf $(NAME).dSYM
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft

re: fclean all
