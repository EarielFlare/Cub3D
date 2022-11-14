#include "get_next_line.h"

void	buf_next_line(char *buf, char **s1)
{
	char	*n;
	char	*s2;

	n = ft_strchr(buf, '\n');
	*n++ = '\0';
	s2 = ft_strjoin(*s1, buf);
	free(*s1);
	*s1 = s2;
	ft_strlcpy(buf, n, ft_strlen(n) + 1);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*s1;
	char		*s2;
	long		last;

	if (read(fd, 0, 0) == -1 || BUFFER_SIZE < 1)
		return (NULL);
	last = 1;
	s1 = ft_strdup("");
	while (!(ft_strchr(buf, '\n')) && last > 0)
	{
		s2 = ft_strjoin(s1, buf);
		free(s1);
		s1 = s2;
		last = read(fd, buf, BUFFER_SIZE);
		buf[last] = '\0';
	}
	if (last < 0 || (last == 0 && s1[0] == '\0'))
	{
		free (s1);
		return (NULL);
	}
	if (ft_strchr(buf, '\n'))
		buf_next_line(buf, &s1);
	return (s1);
}
