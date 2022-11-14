#include "cub3d.h"

void	rays_prep(t_vars *p_vars)
{
	int	ray_cnt;

	ray_cnt = p_vars->raynum;
	p_vars->ray_step = p_vars->player.fov / (p_vars->raynum - 1);
	while(ray_cnt--)
	{
		p_vars->ray[ray_cnt].dist_horz = p_vars->map_size_max;
		p_vars->ray[ray_cnt].dist_vert = p_vars->map_size_max;
		p_vars->ray[ray_cnt].ray_dir = p_vars->player.dir
			- (p_vars->player.fov / 2) + (p_vars->ray_step * ray_cnt);
	}
}

void	sincos_prep(t_vars *p_vars)
{
	p_vars->player.sinf_dir0 = sinf((M_PI / 180) * (p_vars->player.dir));
	p_vars->player.cosf_dir0 = cosf((M_PI / 180) * (p_vars->player.dir));
	p_vars->player.sinf_dir180 = -p_vars->player.sinf_dir0;
	p_vars->player.cosf_dir180 = -p_vars->player.cosf_dir0;
	p_vars->player.sinf_dir90 = p_vars->player.cosf_dir180;
	p_vars->player.cosf_dir90 = p_vars->player.sinf_dir0;
	p_vars->player.sinf_dir_90 = -p_vars->player.sinf_dir90;
	p_vars->player.cosf_dir_90 = -p_vars->player.cosf_dir90;
	p_vars->player.sinf_dir45 = sinf((M_PI / 180) * (p_vars->player.dir + 45));
	p_vars->player.cosf_dir45 = cosf((M_PI / 180) * (p_vars->player.dir + 45));
	p_vars->player.sinf_dir225 = -p_vars->player.sinf_dir45;
	p_vars->player.cosf_dir225 = -p_vars->player.cosf_dir45;
	p_vars->player.sinf_dir135 = p_vars->player.cosf_dir45;
	p_vars->player.cosf_dir135 = -p_vars->player.sinf_dir45;
	p_vars->player.sinf_dir_45 = -p_vars->player.cosf_dir45;
	p_vars->player.cosf_dir_45 = p_vars->player.sinf_dir45;
}

void	player_move(t_vars *p_vars, double sinf, double cosf)
{
	int	ray_cnt;
	double pos_x;
	double pos_y;

	pos_y = p_vars->player.pos.y - p_vars->player.step * sinf;
	pos_x = p_vars->player.pos.x + p_vars->player.step * cosf;
	if (pos_y > 0 && pos_y < p_vars->map_sizei)
		p_vars->player.pos.y = pos_y;
	if (pos_x > 0 && pos_x < p_vars->map_sizej)
		p_vars->player.pos.x = pos_x;
	ray_cnt = p_vars->raynum;
	while(ray_cnt--)
	{
		p_vars->ray[ray_cnt].dist_horz = p_vars->map_size_max;
		p_vars->ray[ray_cnt].dist_vert = p_vars->map_size_max;
	}
}

void	kbrd_hook_check(t_vars *p_vars)
{
	if (p_vars->player.forward && p_vars->player.leftward)
		player_move(p_vars, p_vars->player.sinf_dir45, p_vars->player.cosf_dir45);
	else if (p_vars->player.forward && p_vars->player.rightward)
		player_move(p_vars, p_vars->player.sinf_dir_45, p_vars->player.cosf_dir_45);
	else if (p_vars->player.backward && p_vars->player.leftward)
		player_move(p_vars, p_vars->player.sinf_dir135, p_vars->player.cosf_dir135);
	else if (p_vars->player.backward && p_vars->player.rightward)
		player_move(p_vars, p_vars->player.sinf_dir225, p_vars->player.cosf_dir225);
	if (p_vars->player.forward && !p_vars->player.leftward && !p_vars->player.rightward)
		player_move(p_vars, p_vars->player.sinf_dir0, p_vars->player.cosf_dir0);
	else if (p_vars->player.backward && !p_vars->player.leftward && !p_vars->player.rightward)
		player_move(p_vars, p_vars->player.sinf_dir180, p_vars->player.cosf_dir180);
	else if (p_vars->player.leftward && !p_vars->player.forward && !p_vars->player.backward)
		player_move(p_vars, p_vars->player.sinf_dir_90, p_vars->player.cosf_dir_90);
	else if (p_vars->player.rightward && !p_vars->player.forward && !p_vars->player.backward)
		player_move(p_vars, p_vars->player.sinf_dir90, p_vars->player.cosf_dir90);
}

int	key_hook_press(int keycode, t_vars *p_vars)
{
	if (keycode == 13){			//	up
		p_vars->player.forward = 1;
	}
	else if (keycode == 1){		//	down
		p_vars->player.backward = 1;
	}
	else if (keycode == 0){		//	left
		p_vars->player.leftward = 1;
	}
	else if (keycode == 2){		//	right
		p_vars->player.rightward = 1;
	}
	else if (keycode == 123){	//	turn left
		p_vars->player.dir += 1;
		rays_prep(p_vars);
		sincos_prep(p_vars);
	}
	else if (keycode == 124){	//	turn right
		p_vars->player.dir -= 1;
		rays_prep(p_vars);
		sincos_prep(p_vars);
	}
	else if (keycode == 53)
		close_win(p_vars);
	else if (keycode == 4)
		p_vars->img.is_help = !p_vars->img.is_help;
	return (0);
}

int	key_hook_release(int keycode, t_vars *p_vars)
{
	if (keycode == 13)			//	up
		p_vars->player.forward = 0;
	else if (keycode == 1)		//	down
		p_vars->player.backward = 0;
	else if (keycode == 0)		//	left
		p_vars->player.leftward = 0;
	else if (keycode == 2)		//	right
		p_vars->player.rightward = 0;
	return (0);
}

int	mouse_move(int x, int y, t_vars *p_vars)
{
	(void)y;
	if (p_vars->img.btn2_down == 1)
		{
		p_vars->player.divider = (-x + p_vars->img.mouse_x) % (360 * p_vars->player.sense);
		p_vars->player.dir += (float)p_vars->player.divider / p_vars->player.sense;
		rays_prep(p_vars);
		sincos_prep(p_vars);
		p_vars->img.mouse_x = x;
	}
	return (0);
}

int	mouse_hook_press(int keycode, int x, int y, t_vars *p_vars)
{
	(void)y;
	if (keycode == 2){
		p_vars->img.btn2_down = 1;
		p_vars->img.mouse_x = x;
	}
	return (0);
}

int	mouse_hook_release(int keycode, int x, int y, t_vars *p_vars)
{
	(void)x;
	(void)y;
	if (keycode == 2)
		p_vars->img.btn2_down = 0;
	return (0);
}
