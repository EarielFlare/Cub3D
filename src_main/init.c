#include "cub3d.h"

void	init_image(t_vars *p_vars)
{
	p_vars->img.img = mlx_new_image(p_vars->mlx,
		p_vars->win_width, p_vars->win_height);
	p_vars->img.addr = mlx_get_data_addr(p_vars->img.img,
		&p_vars->img.bits_per_pixel, &p_vars->img.line_length,
		&p_vars->img.endian);
}

void	init_program(t_vars *p_vars)
{
	set_defaults(p_vars);
	p_vars->win = mlx_new_window(p_vars->mlx,
		p_vars->win_width, p_vars->win_height, "FRACTOL");
	mlx_hook(p_vars->win, 2, 1L << 0, key_hook_press, p_vars);
	mlx_hook(p_vars->win, 3, 1L << 0, key_hook_release, p_vars);
	mlx_hook(p_vars->win, 4, 1L << 2, mouse_hook_press, p_vars);
	mlx_hook(p_vars->win, 5, 1L << 2, mouse_hook_release, p_vars);
	mlx_hook(p_vars->win, 6, 1L << 6, mouse_move, p_vars);
	mlx_hook(p_vars->win, 17, 0L, close_win, p_vars);
	mlx_loop_hook(p_vars->mlx, while_func, p_vars);
}

void	set_defaults(t_vars *p_vars)
{
	p_vars->win_width = WIDTH;
	p_vars->win_height = HEIGHT;
	p_vars->img.is_help = FALSE;
}
