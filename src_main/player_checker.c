#include "cub3d.h"

void	get_player_direction(char dir, t_vars *p_vars)
{
	if (dir == 'N')	//	up
		p_vars->player.dir = 90;
	if (dir == 'S')	//	down
		p_vars->player.dir = 270;
	if (dir == 'W')	//	left
		p_vars->player.dir = 180;
	if (dir == 'E')	//	right
		p_vars->player.dir = 0;
}

void	player_pos_check(t_vars *p_vars, int x, int y)
{
	if (p_vars->map[y][x] == 'N' || p_vars->map[y][x] == 'S'
				|| p_vars->map[y][x] == 'E' || p_vars->map[y][x] == 'W')
	{
		if (p_vars->player.pos.x > 0 || p_vars->player.pos.y > 0)
			ft_exit("Error: too many player positions\n");
		get_player_direction(p_vars->map[y][x], p_vars);
		p_vars->player.pos.y = y + 0.5;
		p_vars->player.pos.x = x + 0.5;
		p_vars->map[y][x] = '0';
	}
}

void	find_player_pos(t_vars *p_vars)
{
	int	x;
	int	y;

	y = 0;
	while (p_vars->map[y])
	{
		x = 0;
		while (p_vars->map[y][x])
		{
			player_pos_check(p_vars, x, y);
			x++;
		}
		y++;
	}
	if (p_vars->player.pos.x < 0 || p_vars->player.pos.y < 0)
		ft_exit("Error: no designated player position\n");
}
