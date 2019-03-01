#include "ft_ssl.h"

uint32_t get_options(int argc, char *argv[])
{
	uint32_t options;

	(void) argc;
	(void) argv;
	options = 0;
	options |= I;
	return (options);
}

void	*ft_realloc(void *src, size_t old_size, size_t new_size)
{
	void *new;

	new = xv(ft_memalloc(new_size), MALLOC);
	ft_memcpy(new, src, old_size);
	return (new);
}

char	*get_input_string(void)
{
	char	buff;
	size_t	len;
	size_t	size;
	char	*str;

	size = 1000;
	str = xv(ft_strnew(size), MALLOC);
	len = 0;
	while (x(read(STDIN_FILENO, &buff, 1), READ))
	{
		if (len >= size)
			str = xv(ft_realloc(str, size, size * 2), MALLOC);
		str[len++] = buff;
	}
	return (str);
}

char	*convert_string(t_env *env, char *str)
{
	char *conv_str;

	(void)env;
	conv_str = md5(str);
	return (conv_str);
}

int read_from_stdin(t_env *env)
{
	char	*str;

	str = get_input_string();
	convert_string(env, str);
	/* print_str(env, hash_str); */
	return (0);
}

int main(int argc, char *argv[])
{
	t_env env;

	ft_bzero(&env, sizeof(env));
	env.options = get_options(argc, argv);
	return (read_from_stdin(&env));
}
