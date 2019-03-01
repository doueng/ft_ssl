#ifndef FT_SSL_H
# define FT_SSL_H

# include "./libft/libft.h"

# define snums1 "7 12 17 22 7 12 17 22 7 12 17 22 7 12 17 22"
# define snums2 "5 9 14 20 5 9 14 20 5 9 14 20 5 9 14 20"
# define snums3 "11 16 23 4 11 16 23 4 11 16 23 4 11 16 23"
# define snums4 "10 15 21 6 10 15 21 6 10 15 21 6 10 15 21"

typedef struct	s_env
{
	uint32_t	options;
}				t_env;

enum
{
	I,
	P,
	Q,
	R,
	S
};

enum
{
	READ,
	OPEN,
	CLOSE,
	WRITE,
	MALLOC,
	USAGE,
	INVALID_OPTION,
	SPLIT
};

char		*md5(char *str);
int			x(int res, int error);
void		*xv(void *res, int error);
uint32_t	revbytes32(uint32_t bytes);

#endif
