#include "ft_ssl.h"

static void	*ft_realloc(void *src, size_t old_size, size_t new_size)
{
	void *new;

	new = xv(ft_memalloc(new_size), MALLOC);
	ft_memcpy(new, src, old_size);
	free(src);
	return (new);
}

static char	*get_fd_string(int fd)
{
	char	buff;
	size_t	len;
	size_t	size;
	char	*str;
	int		ret;

	size = 100;
	str = xv(ft_strnew(size), MALLOC);
	len = 0;
	errno = 0;
	while ((ret = (read(fd, &buff, 1))))
	{
		if (errno == EAGAIN)
			break ;
		x(ret, READ);
		if (len >= size)
		{
			str = xv(ft_realloc(str, size, size * 2), MALLOC);
			size *= 2;
		}
		str[len++] = buff;
	}
	if (fd != 0)
		x(close(fd), CLOSE);
	return (str);
}

int				read_from_fd(t_env *env, char *arg, int fd)
{
	char	*str;

	str = get_fd_string(fd);
	if (ft_strlen(str) > 0)
		hasher(env, arg, str, fd == STDIN_FILENO ? STDIN : FILE);
	free(str);
	return (0);
}
