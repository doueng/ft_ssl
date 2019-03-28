NAME = ./ft_ssl
HEADER = ./ft_ssl.h
LIB = ./libft/libft.a
FLAGS = -Werror -Wextra -Wall -g
SRC = get_options.c \
		hash_utils.c \
		hasher.c \
		main.c \
		md5.c \
		md5_calc.c \
		printer.c \
		process_args.c \
		read_from_fd.c \
		revbytes.c \
		sha256.c \
		x.c

SRCO = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRCO) $(HEADER)
	make -C libft
	gcc $(SRCO) $(LIB) -o $(NAME)

%.o: %.c
	gcc -c $(FLAGS) $< -o $@

clean:
	/bin/rm -f $(SRCO)
	make clean -C libft

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft

re: fclean all
