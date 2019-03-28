/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:22:53 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/23 19:22:54 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_p(t_env *env, char *arg, char source)
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

static void	print_p_rev(t_env *env, char *arg, char source)
{
	if (env->options & R_OP && source != STDIN)
		source == FILE
			? ft_printf(" %s", arg)
			: ft_printf(" \"%s\"", arg);
}

void		print_hash(t_env *env, char *arg, t_hash *hash, char source)
{
	uint32_t	i;
	char		print;

	i = 0;
	print = (env->options & Q_OP) == 0 &&
		(env->options & P_OP || source == FILE || source == STR);
	if (print)
		print_p(env, arg, source);
	while (hash->num_parts--)
		ft_printf("%08x", hash->parts[i++]);
	if (print)
		print_p_rev(env, arg, source);
	ft_putchar('\n');
}
