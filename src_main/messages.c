#include "cub3d.h"

void	print_prompt(void)
{
	ft_putendl("Usage: ./fractol <name>");
	ft_putendl("You can specify from 1 to 2 names of fractals");
	ft_putendl("List of available fractals:");
	ft_putendl(" ⚬➡️	Julia");
	ft_putendl(" ⚬➡️	Mandelbrot");
}

void	draw_help_1(t_vars *p_vars)
{
	mlx_string_put(p_vars->mlx, p_vars->win, 115, 40, 0x0000FFCC,
		"Controls");
	mlx_string_put(p_vars->mlx, p_vars->win, 40, 65, 0x0000FFCC,
		"Zoom           - Scroll");
	mlx_string_put(p_vars->mlx, p_vars->win, 40, 90, 0x0000FFCC,
		"Move           - Arrows");
	mlx_string_put(p_vars->mlx, p_vars->win, 40, 115, 0x0000FFCC,
		"Mouse Lock     - Space");
	mlx_string_put(p_vars->mlx, p_vars->win, 40, 140, 0x0000FFCC,
		"Iterations     - + / -");
	mlx_string_put(p_vars->mlx, p_vars->win, 40, 165, 0x0000FFCC,
		"Contrast       - Q / E");
	mlx_string_put(p_vars->mlx, p_vars->win, 40, 190, 0x0000FFCC,
		"Brightness     - A / D");
	mlx_string_put(p_vars->mlx, p_vars->win, 40, 215, 0x0000FFCC,
		"Close Help     - H");
}
