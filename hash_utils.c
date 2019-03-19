#include "ft_ssl.h"

uint64_t	get_new_len(uint64_t input_len)
{
	uint64_t new_len;

	new_len = input_len * 8 + 1;
	while (new_len % 512 != 448)
		new_len++;
	return (new_len / 8);
}

uint32_t	rightrotate32(uint32_t num, uint32_t rotate_size)
{
	uint32_t r;

	r = rotate_size % 32;
	return ((num >> r) | (num << (32 - r)));
}

void		add_chunk_to_hash(t_hash *hash, uint32_t *tmp)
{
	size_t i;

	i = 0;
	while (i < hash->num_parts)
	{
		hash->parts[i] += tmp[i];
		i++;
	}
}

void		rev_hash32(t_hash *hash)
{
	size_t i;

	i = 0;
	while (i < hash->num_parts)
	{
		hash->parts[i] = revbytes32(hash->parts[i]);
		i++;
	}
}
