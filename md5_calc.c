/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:18:08 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/23 19:18:09 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	calc_g(uint32_t i)
{
	uint32_t g;

	g = 0;
	if (i < 16)
		g = i;
	else if (16 <= i && i <= 31)
		g = (5 * i + 1) % 16;
	else if (32 <= i && i <= 47)
		g = (3 * i + 5) % 16;
	else if (48 <= i && i <= 63)
		g = (7 * i) % 16;
	return (g);
}

uint32_t	calc_f(uint32_t i, uint32_t b, uint32_t c, uint32_t d)
{
	uint32_t f;

	f = 0;
	if (i < 16)
		f = (b & c) | ((~b) & d);
	else if (16 <= i && i <= 31)
		f = (d & b) | ((~d) & c);
	else if (32 <= i && i <= 47)
		f = b ^ c ^ d;
	else if (48 <= i && i <= 63)
		f = c ^ (b | (~d));
	return (f);
}
