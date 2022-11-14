#include "cub3d.h"

void	check_file(char *file, t_vars *p_vars)
{
	int	fd;

	if (ft_strlen(file) < 5
		|| !ft_strnstr(file + (ft_strlen(file) - 4), ".cub", 4))
		ft_exit("Error! Need map .cub");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_exit("Error! Arg is not file");
	check_file_argv(fd, p_vars);
	find_player_pos(p_vars);
}

void	check_file_argv(int fd, t_vars *p_vars)
{
	char	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		if (its_not_map(p_vars, str) && its_map_line(str))
		{
			check_assets(p_vars);
			return (create_map(p_vars, str, fd));
		}
		free(str);
		str = get_next_line(fd);
	}
}

void	create_map(t_vars *p_vars, char *str, int fd)
{
	int	i;

	i = 0;
	p_vars->map = ft_calloc(sizeof(char *), 101);
	while (str != NULL)
	{
		map_line_check(str);
		if (i > 100)
			ft_exit("Error: map too big\n");
		p_vars->map[i] = ft_strdup(str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	close (fd);
	map_check(p_vars);
}

void	map_check(t_vars *p_vars)
{
	int	i;
	int	j;

	i = 1;
	small_map_check(p_vars);
	border_zero_check(p_vars);
	while (p_vars->map[i + 1])
	{
		j = 1;
		while (p_vars->map[i][j + 1])
		{
			if (p_vars->map[i][j] == ' ')
				border_void_check(p_vars, i, j);
			j++;
		}
		i++;
	}
}
