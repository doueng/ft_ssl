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

t_hash_func	get_hash_func(char *cmd)
{
	t_hash_func	hash_func;

	hash_func = NULL;
	hash_func = ft_strequ(cmd, "md5") ? md5 : hash_func;
	hash_func = ft_strequ(cmd, "sha256") ? sha256 : hash_func;
	return (hash_func);
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
		read_from_fd(&env, "", STDIN_FILENO);
	process_args(&env, argv + 1);
	return (0);
}
