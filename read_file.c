/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:39:28 by dengstra          #+#    #+#             */
/*   Updated: 2019/04/17 14:39:29 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			read_file(t_env *env, char *arg, int fd)
{
	char		*str;
	struct stat	st;

	x(fstat(fd, &st), STAT);
	str = xv(malloc(st.st_size), MALLOC);
	env->input_size = st.st_size;
	x(read(fd, str, st.st_size), MALLOC);
	hasher(env, arg, str, FILE);
	free(str);
	return (0);
}
