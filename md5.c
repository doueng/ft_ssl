#include "ft_ssl.h"

uint32_t	calc_g(uint32_t i)
{
	uint32_t g;

	g = 0;
	if (i < 16)
		g = i;
	else if (16 <= i && i <= 31)
		g = (5*i + 1) % 16;
	else if (32 <= i && i <= 47)
		g = (3*i + 5) % 16;
	else if (48 <= i && i <= 63)
		g = (7*i) % 16;
	return (g);
}

uint32_t	calc_f(uint32_t i,
				   uint32_t b,
				   uint32_t c,
				   uint32_t d)
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

void		update_hash(uint32_t *hash,
					uint32_t *w,
					uint32_t *k,
					uint32_t *s)
{
	uint32_t f;
	uint32_t i;
	uint32_t tmp[4];

	i = 0;
	ft_memcpy(tmp, hash, sizeof(uint32_t) * 4);
	while (i < 64)
	{
		f = calc_f(i, tmp[1], tmp[2] , tmp[3]);
		f += tmp[0] + k[i] + w[calc_g(i)];
		tmp[0] = tmp[3];
		tmp[3] = tmp[2];
		tmp[2] = tmp[1];
		tmp[1] += f << s[i] | f >> (32 - s[i]);
		i++;
	}
	hash[0] += tmp[0];
	hash[1] += tmp[1];
	hash[2] += tmp[2];
	hash[3] += tmp[3];
}

void	filler(uint32_t *s, char *nums)
{
	char	**split;
	int		i;

	i = 0;
	split = xv(ft_strsplit(nums, ' '), SPLIT);
	while (split[i])
	{
		s[i] = ft_atoi(split[i]);
		i++;
	}
	ft_free_split(split);
}

void	fill_s(uint32_t *s)
{
	filler(s, "7 12 17 22 7 12 17 22 7 12 17 22 7 12 17 22");
	filler(s + 16, "5 9 14 20 5 9 14 20 5 9 14 20 5 9 14 20");
	filler(s + 32, "4 11 16 23 4 11 16 23 4 11 16 23 4 11 16 23");
	filler(s + 48, "6 10 15 21 6 10 15 21 6 10 15 21 6 10 15 21");
}

void	init_hash(t_hash *hash)
{
	hash->num_parts = 4;
	hash->parts = xv(malloc(sizeof(uint32_t) * 4), MALLOC);
	hash->parts[0] = 0x67452301;
	hash->parts[1] = 0xefcdab89;
	hash->parts[2] = 0x98badcfe;
	hash->parts[3] = 0x10325476;
}

t_hash	*md5(t_hash *hash, char *input)
{
	size_t		input_len;
	size_t		new_len;
	char		*msg;
	uint32_t	s[64];
	uint32_t k[] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
	fill_s(s);
	init_hash(hash);
	input_len = ft_strlen(input);
	for (new_len = input_len * 8 + 1; new_len % 512 != 448; new_len++)
		;
	new_len /= 8;
	msg = xv(ft_memalloc(new_len + 64), MALLOC);
	ft_memcpy(msg, input, input_len);
	msg[input_len] = 0x80;
	uint32_t bits_len = 8 * input_len;
	ft_memcpy(msg + new_len, &bits_len, 4);
	size_t offset;
	for (offset = 0; offset < new_len; offset += (512 / 8))
	{
		uint32_t *w = (uint32_t *) (msg + offset);
		update_hash(hash->parts, w, k, s);
	}
	return (hash);
}
