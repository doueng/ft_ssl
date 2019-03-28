/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:18:20 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/23 19:18:22 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t g_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void		init_hash(t_hash *hash)
{
	hash->num_parts = 8;
	hash->parts = xv(malloc(sizeof(uint32_t) * 8), MALLOC);
	hash->parts[0] = 0x6a09e667;
	hash->parts[1] = 0xbb67ae85;
	hash->parts[2] = 0x3c6ef372;
	hash->parts[3] = 0xa54ff53a;
	hash->parts[4] = 0x510e527f;
	hash->parts[5] = 0x9b05688c;
	hash->parts[6] = 0x1f83d9ab;
	hash->parts[7] = 0x5be0cd19;
}

static uint8_t	*get_msg(uint64_t input_len,
				uint64_t new_len,
				char *input)
{
	uint64_t	bits_len;
	uint8_t		*msg;

	msg = xv(ft_memalloc(new_len + 8), MALLOC);
	ft_memcpy(msg, input, input_len);
	msg[input_len] = 0x80;
	bits_len = 8 * input_len;
	bits_len = rev64(bits_len);
	ft_memcpy(msg + new_len, &bits_len, 8);
	return (msg);
}

static void		update_hash(t_hash *hash, uint32_t *w)
{
	uint32_t	h[8];
	uint32_t	tmp[8];
	size_t		i;

	ft_memcpy(h, hash->parts, sizeof(h));
	i = 0;
	while (i < 64)
	{
		tmp[0] = rightrotate32(h[4], 6)
			^ rightrotate32(h[4], 11) ^ rightrotate32(h[4], 25);
		tmp[1] = (h[4] & h[5]) ^ ((~h[4]) & h[6]);
		tmp[2] = h[7] + tmp[0] + tmp[1] + g_k[i] + w[i];
		tmp[3] = rightrotate32(h[0], 2)
			^ rightrotate32(h[0], 13) ^ rightrotate32(h[0], 22);
		tmp[4] = (h[0] & h[1]) ^ (h[0] & h[2]) ^ (h[1] & h[2]);
		tmp[5] = tmp[3] + tmp[4];
		tmp[6] = h[3];
		ft_memmove(h + 1, h, sizeof(h) - 4);
		h[4] = tmp[6] + tmp[2];
		h[0] = tmp[2] + tmp[5];
		i++;
	}
	add_chunk_to_hash(hash, h);
}

static void		prepare_words(uint32_t *w, uint8_t *msg, size_t offset)
{
	size_t		i;
	uint32_t	s0;
	uint32_t	s1;

	ft_bzero(w, sizeof(w));
	ft_memcpy(w, msg + offset, 64);
	i = 0;
	while (i < 16)
	{
		w[i] = revbytes32(w[i]);
		i++;
	}
	i = 16;
	while (i < 64)
	{
		s0 = rightrotate32(w[i - 15], 7)
			^ rightrotate32(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = rightrotate32(w[i - 2], 17)
			^ rightrotate32(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		i++;
	}
}

void			sha256(t_hash *hash, char *input)
{
	uint64_t	input_len;
	uint64_t	new_len;
	uint8_t		*msg;
	uint32_t	w[64];
	size_t		offset;

	init_hash(hash);
	input_len = ft_strlen(input);
	new_len = get_new_len(input_len);
	msg = get_msg(input_len, new_len, input);
	new_len += 8;
	offset = 0;
	while (offset < new_len)
	{
		prepare_words(w, msg, offset);
		update_hash(hash, w);
		offset += 64;
	}
}
