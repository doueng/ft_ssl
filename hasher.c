#include "ft_ssl.h"

static char	ft_toupper_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}

static void	print_hash(t_env *env, t_hash *hash, char is_file)
{
	uint32_t	i;

	i = 0;
	ft_strmap(env->cmd, ft_toupper_char);
	if (env->options & P_OP && !(env->options & R_OP))
		is_file == IS_FILE
			? ft_printf("%s (%s) = ", env->cmd, hash->name)
			: ft_printf("%s (\"%s\") = ", env->cmd, hash->name);
	while (hash->num_parts--)
		ft_printf("%x", revbytes32(hash->parts[i++]));
	if (env->options & P_OP && env->options & R_OP)
		is_file == IS_FILE
			? ft_printf(" %s", hash->name)
			: ft_printf(" \"%s\"", hash->name);
	ft_putchar('\n');
}

void		hasher(t_env *env, char *str, char is_file)
{
	t_hash *hash;

	(void)env;
	hash = xv(malloc(sizeof(t_hash)), MALLOC);
	hash->name = str;
	if (env->options & MD5)
		hash = md5(hash, str);
	print_hash(env, hash, is_file);
}
