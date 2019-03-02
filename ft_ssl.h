#ifndef FT_SSL_H
# define FT_SSL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <errno.h>

typedef struct	s_env
{
	uint32_t	options;
	char		*cmd;
}				t_env;

typedef struct	s_hash
{
	uint32_t	*parts;
	size_t		num_parts;
	char		*name;
}				t_hash;

enum
{
	IS_FILE,
	IS_STR,
	MD5,
	SHA256,
	I_OP,
	P_OP,
	Q_OP,
	R_OP,
	S_OP
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

t_hash		*md5(t_hash *hash, char *input);
void		hasher(t_env *env, char *str, char is_file);
uint32_t	get_options(int argc, char *argv[]);
int			x(int res, int error);
void		*xv(void *res, int error);
uint32_t	revbytes32(uint32_t bytes);
int			read_from_fd(t_env *env, int fd);

#endif
