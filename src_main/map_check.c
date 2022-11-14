#include "cub3d.h"

void	ft_exit(char *err)
{
	if (err)
		printf("%s\n", err);
	exit(1);
}

void	map_line_check(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		ft_exit("Error: map line is empty");
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != ' '
			&& str[i] != 'W' && str[i] != 'E' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != '\n')
			{
				free(str);
				ft_exit("Error: invalid parameters");
			}
		i++;
	}
}

int	dpl(char *arg)
{
	if (arg != NULL)
		ft_exit("Error: double parameters\n");
	return (0);
}

int	its_not_map(t_vars *vars, char *str)
{
	char	**argv;
	int		ret;

	ret = 0;
	if (ft_strlen(str) == 0)
		return (0);
	argv = ft_split(str, ' ');
	if (!ft_strncmp(argv[0], "NO", 2) && !dpl(vars->assets.north_wall))
		vars->assets.north_wall = ft_strdup(argv[1]);
	else if (!ft_strncmp(argv[0], "SO", 2) && !dpl(vars->assets.south_wall))
		vars->assets.south_wall = ft_strdup(argv[1]);
	else if (!ft_strncmp(argv[0], "WE", 2) && !dpl(vars->assets.west_wall))
		vars->assets.west_wall = ft_strdup(argv[1]);
	else if (!ft_strncmp(argv[0], "EA", 2) && !dpl(vars->assets.east_wall))
		vars->assets.east_wall = ft_strdup(argv[1]);
	else if (!ft_strncmp(argv[0], "F", 1) && !dpl(vars->assets.floor))
		vars->assets.floor = ft_strdup(argv[1]);
	else if (!ft_strncmp(argv[0], "C", 1) && !dpl(vars->assets.ceiling))
		vars->assets.ceiling = ft_strdup(argv[1]);
	else
		ret = 1;
	ft_free_split(argv);
	return (ret);
}

int	its_map_line(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0' || ft_strlen(str) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

char	**ft_free_split(char *split[])
{
	int	i;

	i = 0;
	if (!split)
		return (NULL);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

void	check_assets(t_vars *vars)
{
	if (!vars->assets.north_wall || !vars->assets.south_wall
		|| !vars->assets.east_wall || !vars->assets.west_wall
		|| !vars->assets.ceiling || !vars->assets.floor)
		ft_exit("Error: not enough assets\n");
}

