#include "cub3d.h"

void	small_map_check(t_vars *vars)
{
	int	i;

	i = 0;
	if (!vars->map)
		ft_exit("Error: no map\n");
	while (vars->map[i])
	{
		if (ft_strlen(vars->map[i]) < 3)
			ft_exit("Error: map is too small2\n");
		i++;
	}
	if (i < 3)
		ft_exit("Error: map is too small\n");
}

void	border_zero_check(t_vars *vars)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	while (vars->map[0][j])
	{
		if (vars->map[0][j] == '0' ||
			(vars->map[0][j] == ' ' && vars->map[1][j] == '0'))
			flag = 1;
		j++;
	}
	check_we_ea_so_border(vars, &flag);
	check_east_border(vars, &flag);
	if (flag == 1)
		ft_exit("Error: map without borders\n");
}

void	border_void_check(t_vars *vars, int i, int j)
{
	if (vars->map[i + 1][j] == '0' || vars->map[i][j + 1] == '0'
		|| vars->map[i - 1][j] == '0' || vars->map[i][j - 1] == '0')
		ft_exit("Error: map without borders\n");
}

void	check_we_ea_so_border(t_vars *vars, int *flag)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map[i])
	{
		j = ft_strlen(vars->map[i]) - 1;
		if (vars->map[i][0] == '0' || vars->map[i][j] == '0' ||
			(vars->map[i][0] == ' ' && vars->map[i][1] == '0') ||
			(vars->map[i][j] == ' ' && vars->map[i][j - 1] == '0'))
			*flag = 1;
		i++;
	}
	j = 0;
	while (vars->map[i - 1][j])
	{
		if (vars->map[i - 1][j] == '0' ||
			(vars->map[i - 1][j] == ' ' && vars->map[i - 2][j] == '0'))
			*flag = 1;
		j++;
	}
}

void	check_east_border(t_vars *vars, int *flag)
{
	int	len;
	int	i;
	int	j;

	i = 1;
	while (vars->map[i + 1])
	{
		j = 1;
		len = ft_strlen(vars->map[i]) - 1;
		while (j < len)
		{
			if (vars->map[i][j] == '0' &&
				(vars->map[i - 1][j] == ' ' || vars->map[i + 1][j] == ' ' ||
				vars->map[i][j - 1] == ' ' || vars->map[i][j + 1] == ' ' ||
				vars->map[i - 1][j] == '\0' || vars->map[i + 1][j] == '\0' ||
				vars->map[i][j - 1] == '\0' || vars->map[i][j + 1] == '\0'))
				*flag = 1;
			j++;
		}
		i++;
	}
}
