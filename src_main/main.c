#include "cub3d.h"

int	g_flag;

int	render_func(void *strct)
{
	t_vars	*vars;
	vars = (t_vars *)strct;

	init_image(vars);
	kbrd_hook_check(vars);
	calc_map(vars, &vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	if (vars->img.is_help)
		draw_help_1(vars);
	mlx_destroy_image(vars->mlx, vars->img.img);
	g_flag = 0;
	return (0);
}

int	while_func(void *strct)
{
	if (g_flag == 1)
		render_func(strct);
	return (0);
}

void timer_handler(int signum)
{
	(void)signum;
	g_flag = 1;
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_vars	*p_vars;
	struct sigaction sa;
	struct itimerval timer;

	g_flag = 0;
	memset (&sa, 0, sizeof (sa));
	sa.sa_handler = &timer_handler;
	sigaction (SIGALRM, &sa, NULL);
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 25000;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 25000;
	setitimer (ITIMER_REAL, &timer, NULL);

	if (argc != 2)
		ft_exit("Error! Need map ./cub3d maps/map.cub");
	p_vars = &vars;
	init_vars(&vars);
	check_file(argv[1], &vars);
	measure_map(p_vars);
//	p_vars->player.dir = 45;
	rays_prep(p_vars);
	sincos_prep(p_vars);

	p_vars->horz_walls = make_array(p_vars, 1, 0);
	p_vars->vert_walls = make_array(p_vars, 0, 1);
	fill_with_sp(p_vars, p_vars->horz_walls, 1, 0);
	fill_with_sp(p_vars, p_vars->vert_walls, 0, 1);
	fill_with_val(p_vars);
	vars.mlx = mlx_init();
	init_program(p_vars);
	mlx_loop(vars.mlx);
	free_array(p_vars, p_vars->horz_walls, 1);
	free_array(p_vars, p_vars->vert_walls, 0);
	return (0);
}
