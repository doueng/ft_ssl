/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:17:58 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/23 19:18:00 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const static t_arrhash g_funcs[2] = {{"md5", md5}, {"sha256", sha256}};

t_hash_func	get_hash_func(char *cmd)
{
	int i;

	i = sizeof(g_funcs) / sizeof(t_arrhash);
	while (i--)
	{
		if (ft_strequ(g_funcs[i].name, cmd))
			return (g_funcs[i].hash_func);
	}
	return (NULL);
}

int			main(int argc, char *argv[])
{
	t_env	env;

	if (argc < 2)
		x(-1, USAGE);
	ft_bzero(&env, sizeof(env));
	argv++;
	env.cmd = *argv;
	env.hash_func = xv(get_hash_func(*argv), CMD);
	env.options = get_options(argv);
	if ((env.options & ARGS && env.options & P_OP)
		|| ((env.options & ARGS) == 0))
		read_stdin(&env);
	process_args(&env, argv + 1);
	return (0);
}
