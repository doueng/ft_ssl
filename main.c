#include "ft_ssl.h"

void	process_args(t_env *env, char *argv[])
{
	int		fd;

	while (*argv && **argv == '-')
		argv++;
	if (!*argv)
		return ;
	if ((fd = open(*argv, 0, O_RDONLY)) == -1)
		hasher(env, *argv, *argv, STR);
	else
		read_from_fd(env, *argv, fd);
	fd = 0;
	while (*++argv)
	{
		if ((fd = open(*argv, 0, O_RDONLY)) != -1)
			read_from_fd(env, *argv, fd);
		else
			ft_printf("ft_ssl: md5: %s: No such file or directory\n", *argv);
	}
}

int main(int argc, char *argv[])
{
	t_env env;

	if (argc < 2)
		x(-1, USAGE);
	ft_bzero(&env, sizeof(env));
	argv++;
	env.cmd = *argv;
	env.options = get_options(argc, argv + 1);
	read_from_fd(&env, "", STDIN_FILENO);
	process_args(&env, argv + 1);
	return (0);
}
