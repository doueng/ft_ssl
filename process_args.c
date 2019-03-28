/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:28:55 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/28 20:28:58 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		process_args(t_env *env, char *argv[])
{
	int		fd;

	while (*argv && **argv == '-')
		argv++;
	if (!*argv)
		return ;
	if (env->options & S_OP)
	{
		hasher(env, *argv, *argv, STR);
		argv++;
	}
	while (*argv)
	{
		if ((fd = open(*argv, 0, O_RDONLY)) != -1)
			read_from_fd(env, *argv, fd);
		else
			ft_printf("ft_ssl: md5: %s: No such file or directory\n", *argv);
		argv++;
	}
}
