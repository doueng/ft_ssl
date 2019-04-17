/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hasher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:17:55 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/23 19:17:56 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		hasher(t_env *env, char *arg, char *str, char source)
{
	t_hash hash;

	(env->hash_func)(&hash, str, env->input_size);
	print_hash(env, source == STDIN ? str : arg, &hash, source);
	free(hash.parts);
}
