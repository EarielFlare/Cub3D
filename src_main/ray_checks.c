#include "cub3d.h"

void	draw_ray(t_vars *p_vars, t_data *p_img)
{
	int	radius;
	int	ray_cnt;
	int	x_coord;
	int	y_coord;
	int	x_val;
	int	y_val;
	
	(void)p_img;
	ray_cnt = p_vars->raynum;
	while(ray_cnt--)
	{
		radius = 0;
		x_coord = X_OFS + (WMAPSC * p_vars->player.pos.x);
		y_coord = Y_OFS + (WMAPSC * p_vars->player.pos.y);
		while(radius < (int)roundf(p_vars->ray[ray_cnt].dist_min * WMAPSC))
		{
			x_val = x_coord + radius * p_vars->ray[ray_cnt].cosf_dir;
			y_val = y_coord - radius * p_vars->ray[ray_cnt].sinf_dir;
			if (x_val >= WIDTH || x_val < 0 || y_val >= HEIGHT || y_val < 0)
				break;
			my_mlx_pixel_put(p_img, x_val, y_val, 0x00FF0000);
			radius++;
		}
	}
}

void	horz_inter_check(t_vars *p_vars, int iterator, int ray_cnt, int cnt_dir)
{
	double	inter_x;
	int		arr_index;

	while ((cnt_dir < 0 && iterator)
		|| (cnt_dir > 0 && iterator < p_vars->map_sizei))
	{
		inter_x = (iterator - p_vars->ray[ray_cnt].b_ray) / p_vars->ray[ray_cnt].tanf_dir;
		arr_index = (int)(floor(inter_x));
		if ((arr_index > p_vars->map_sizej - 1) || (arr_index < 0)
			|| (iterator > p_vars->map_sizei) || (iterator < 0))
			return ;
		if (p_vars->horz_walls[iterator][(int)floor(inter_x)] == '-')
		{
			p_vars->ray[ray_cnt].dist_horz
				= (p_vars->player.pos.y - iterator) / p_vars->ray[ray_cnt].sinf_dir;
			break ;
		}
		iterator += cnt_dir / abs(cnt_dir);
	}
}

void	horz_check(t_vars *p_vars, t_data *p_img)
{
	int	k;
	int	index;
	int	ray_cnt;
	
	(void)p_img;
	p_vars->player.pos.y_restr[0] = (int)floor(p_vars->player.pos.y);
	p_vars->player.pos.y_restr[1] = (int)ceil(p_vars->player.pos.y);
	ray_cnt = p_vars->raynum;
	while(ray_cnt--)
	{
		p_vars->ray[ray_cnt].tanf_dir = tanf((M_PI / 180) * (180 - p_vars->ray[ray_cnt].ray_dir));
		if (p_vars->ray[ray_cnt].tanf_dir == 0)
			return ;
		p_vars->ray[ray_cnt].b_ray = p_vars->player.pos.y - (p_vars->player.pos.x * p_vars->ray[ray_cnt].tanf_dir);
		p_vars->ray[ray_cnt].sinf_dir = sinf((M_PI / 180) * (p_vars->ray[ray_cnt].ray_dir));
		p_vars->ray[ray_cnt].cosf_dir = cosf((M_PI / 180) * (p_vars->ray[ray_cnt].ray_dir));
		k = (int)(floor(p_vars->ray[ray_cnt].sinf_dir) + ceil(p_vars->ray[ray_cnt].sinf_dir));	//	1 vs -1
		index = abs((int)(floor(p_vars->ray[ray_cnt].sinf_dir)));
		horz_inter_check(p_vars, p_vars->player.pos.y_restr[index], ray_cnt, -k);	//	-1 vs 1
	}
}

void	vert_inter_check(t_vars *p_vars, int iterator, int ray_cnt, int cnt_dir)
{
	double	inter_y;
	int		arr_index;
	
	while ((cnt_dir < 0 && iterator)
		|| (cnt_dir > 0 && iterator < p_vars->map_sizej))
	{
		inter_y = p_vars->ray[ray_cnt].b_ray + (iterator * p_vars->ray[ray_cnt].tanf_dir);
		arr_index = (int)(floor(inter_y));
		if ((arr_index > p_vars->map_sizei - 1) || (arr_index < 0)
			|| (iterator > p_vars->map_sizej) || (iterator < 0))
			return ;

		if (p_vars->vert_walls[(int)floor(inter_y)][iterator] == '|')
		{
			p_vars->ray[ray_cnt].dist_vert
				= (iterator - p_vars->player.pos.x) / p_vars->ray[ray_cnt].cosf_dir;
			break ;
		}
		iterator += cnt_dir / abs(cnt_dir);
	}
}

void	vert_check(t_vars *p_vars, t_data *p_img)
{
	int	k;
	int	index;
	int	ray_cnt;

	(void)p_img;
	p_vars->player.pos.x_restr[0] = (int)floor(p_vars->player.pos.x);
	p_vars->player.pos.x_restr[1] = (int)ceil(p_vars->player.pos.x);
	ray_cnt = p_vars->raynum;
	while(ray_cnt--)
	{
		p_vars->ray[ray_cnt].tanf_dir = tanf((M_PI / 180) * (180 - p_vars->ray[ray_cnt].ray_dir));
		p_vars->ray[ray_cnt].b_ray = p_vars->player.pos.y - (p_vars->player.pos.x * p_vars->ray[ray_cnt].tanf_dir);
		p_vars->ray[ray_cnt].sinf_dir = sinf((M_PI / 180) * (p_vars->ray[ray_cnt].ray_dir));
		p_vars->ray[ray_cnt].cosf_dir = cosf((M_PI / 180) * (p_vars->ray[ray_cnt].ray_dir));
		k = (int)(floor(p_vars->ray[ray_cnt].cosf_dir) + ceil(p_vars->ray[ray_cnt].cosf_dir));	//	1 vs -1
		index = abs((int)(ceil(p_vars->ray[ray_cnt].cosf_dir)));
		vert_inter_check(p_vars, p_vars->player.pos.x_restr[index], ray_cnt, +k);	//	-1 vs 1
	}
}
