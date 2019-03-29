/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:18:25 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/23 19:18:28 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*get_error_msg(int error)
{
	char *msg;

	ft_putstr_fd("Error: ", 2);
	msg = "ERROR";
	msg = error == READ ? "read failed" : msg;
	msg = error == OPEN ? "open failed" : msg;
	msg = error == CLOSE ? "close failed" : msg;
	msg = error == WRITE ? "write failed" : msg;
	msg = error == MALLOC ? "malloc failed" : msg;
	msg = error == USAGE ?
		"Usage: ./ft_ssl command [command opts] [command args]" : msg;
	msg = error == INVALID_OPTION ? "Invaid option" : msg;
	msg = error == FCNTL ? "fcntl failed" : msg;
	msg = error == SPLIT ? "Split failed" : msg;
	return (msg);
}

static void	cmd_error(void)
{
	ft_putstr_fd("ft_ssl: Error: Invalid command.\n\n", 2);
	ft_putstr_fd("Standard commands:\n\n", 2);
	ft_putstr_fd("Message Digest commands:\nmd5\nsha256\n\n", 2);
	ft_putstr_fd("Cipher commands:\n", 2);
}

int			x(int res, int error)
{
	if (res == -1)
	{
		ft_putendl_fd(get_error_msg(error), 2);
		exit(-1);
	}
	return (res);
}

void		*xv(void *res, int error)
{
	if (res == NULL)
	{
		error == CMD ? cmd_error() : ft_putendl_fd(get_error_msg(error), 2);
		exit(-1);
	}
	return (res);
}
