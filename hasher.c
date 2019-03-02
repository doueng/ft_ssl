#include "ft_ssl.h"

static char	ft_toupper_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}

static void print_p(t_env *env, char *arg, char source)
{
	char *cmd;

	source == STDIN ? ft_putstr(arg) : 0;
	if (!(env->options & R_OP))
	{
		cmd = xv(ft_strmap(env->cmd, ft_toupper_char), MALLOC);
		source == FILE ? ft_printf("%s (%s) = ", cmd, arg) : 0;
		source == STR ? ft_printf("%s (\"%s\") = ", cmd, arg) : 0;
		free(cmd);
	}
}

static void print_p_rev(t_env *env, char *arg, char source)
{
	if (env->options & R_OP && source != STDIN)
		source == FILE
			? ft_printf(" %s", arg)
			: ft_printf(" \"%s\"", arg);
}

static void	print_hash(t_env *env, char *arg, t_hash *hash, char source)
{
	uint32_t	i;
	char		print;

	i = 0;
	print = env->options & P_OP && (env->options & Q_OP) == 0;
	if (print)
		print_p(env, arg, source);
	while (hash->num_parts--)
		ft_printf("%x", revbytes32(hash->parts[i++]));
	if (print)
		print_p_rev(env, arg, source);
	ft_putchar('\n');
}

void		hasher(t_env *env, char *arg, char *str, char source)
{
	t_hash *hash;

	hash = xv(ft_memalloc(sizeof(t_hash)), MALLOC);
	if (ft_strequ(env->cmd, "md5"))
		md5(hash, str);
	print_hash(env, source == STDIN ? str : arg, hash, source);
	free(hash);
}
