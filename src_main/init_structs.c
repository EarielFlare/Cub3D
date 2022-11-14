#include "cub3d.h"

void	init_assets(t_vars *vars)
{
	vars->assets.floor = NULL;
	vars->assets.ceiling = NULL;
	vars->assets.north_wall = NULL;
	vars->assets.south_wall = NULL;
	vars->assets.east_wall = NULL;
	vars->assets.west_wall = NULL;
}

void	init_ray(t_vars *vars)
{
	vars->player.pos.x = -1;
	vars->player.pos.y = -1;
	vars->player.fov = 60;
	vars->player.sense = 5;
	vars->player.step = 0.1;
	vars->img.btn2_down = 0;
	vars->raynum = 200;
	vars->player.forward = 0;
	vars->player.backward = 0;
	vars->player.leftward = 0;
	vars->player.rightward = 0;
	rays_prep(vars);
	sincos_prep(vars);
}

void	init_vars(t_vars *p_vars)
{
	init_assets(p_vars);
	init_ray(p_vars);
	p_vars->map = NULL;
}
