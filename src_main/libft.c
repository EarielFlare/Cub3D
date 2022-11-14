#include "cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i != n) && s1[i] && (s1[i] == s2[i]))
		i++;
	if (i == n)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putendl(char *s)
{
	int	i;

	(void)i;
	if (s)
	{
		while (*s)
		{
			i = write(1, s, 1);
			s++;
		}
		i = write(1, "\n", 1);
	}
}
