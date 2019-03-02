#ifndef FT_SSL_H
# define FT_SSL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <errno.h>

# define P_OP 0b1
# define Q_OP 0b10
# define R_OP 0b100
# define S_OP 0b1000

typedef struct	s_env
{
	uint32_t	options;
	char		*cmd;
}				t_env;

typedef struct	s_hash
{
	uint32_t	*parts;
	size_t		num_parts;
}				t_hash;

enum
{
	FILE,
	STR,
	STDIN,
	MD5,
	SHA256,
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
	FCNTL,
	SPLIT
};

void		md5(t_hash *hash, char *input);
void		hasher(t_env *env, char *arg, char *str, char source);
int			read_from_fd(t_env *env, char *arg, int fd);
uint32_t	get_options(int argc, char *argv[]);
int			x(int res, int error);
void		*xv(void *res, int error);
uint32_t	revbytes32(uint32_t bytes);

#endif
