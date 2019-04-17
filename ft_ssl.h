/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:30:46 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/28 20:30:47 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

# define P_OP 0b1
# define Q_OP 0b10
# define R_OP 0b100
# define S_OP 0b1000
# define ARGS 0b10000

typedef struct	s_hash
{
	uint32_t	*parts;
	size_t		num_parts;
}				t_hash;

typedef void	(*t_hash_func)(t_hash*, char*, size_t);

typedef struct	s_arrhash
{
	char		*name;
	t_hash_func	hash_func;
}				t_arrhash;

typedef struct	s_env
{
	uint32_t	options;
	char		*cmd;
	size_t		input_size;
	t_hash_func	hash_func;
}				t_env;

enum
{
	FILE,
	STR,
	STDIN
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
	CMD,
	STAT,
	SPLIT
};

void			process_args(t_env *env, char *argv[]);
uint64_t		rev64(uint64_t x);
void			print_hash(t_env *env, char *arg, t_hash *hash, char source);
void			rev_hash32(t_hash *hash);
void			add_chunk_to_hash(t_hash *hash, uint32_t *tmp);
uint32_t		rightrotate32(uint32_t num, uint32_t rotate_size);
uint64_t		get_new_len(uint64_t input_len);
uint32_t		get_options(char *argv[]);
uint32_t		calc_f(uint32_t i, uint32_t b, uint32_t c, uint32_t d);
uint32_t		calc_g(uint32_t i);
void			hasher(t_env *env, char *arg, char *str, char source);
int				x(int res, int error);
void			*xv(void *res, int error);
uint32_t		revbytes32(uint32_t bytes);
int				read_stdin(t_env *env);
int				read_file(t_env *env, char *arg, int fd);
void			md5(t_hash *hash, char *input, size_t input_size);
void			sha256(t_hash *hash, char *input, size_t input_size);

#endif
