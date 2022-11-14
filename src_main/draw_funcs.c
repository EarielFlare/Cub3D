#include "cub3d.h"

void	find_dist_min(t_vars *p_vars)
{
	int	ray_cnt;

	ray_cnt = p_vars->raynum;
	while(ray_cnt--)
	{
		if (p_vars->ray[ray_cnt].dist_horz < p_vars->ray[ray_cnt].dist_vert)
			p_vars->ray[ray_cnt].dist_min = p_vars->ray[ray_cnt].dist_horz;
		else
			p_vars->ray[ray_cnt].dist_min = p_vars->ray[ray_cnt].dist_vert;
	}
}

void	calc_map(t_vars *p_vars, t_data *p_img)
{
	calc_walls(p_vars, &p_vars->img, p_vars->horz_walls, 1, 0);
	calc_walls(p_vars, &p_vars->img, p_vars->vert_walls, 0, 1);
	horz_check(p_vars, p_img);
	vert_check(p_vars, p_img);
	find_dist_min(p_vars);
	draw_ray(p_vars, p_img);
}

void	calc_walls(t_vars *p_vars, t_data *p_img, char **array, int endi, int endj)
{
	int	i;
	int	j;
	int	li;
	i = 0;
	while(i < p_vars->map_sizei + endi){
		j = 0;
		while(j < p_vars->map_sizej + endj){
			if (array[i][j] == '-' || array[i][j] == '|'){
				li = -1;
				while(++li < WMAPSC)
					my_mlx_pixel_put(p_img, X_OFS + (li * endi) + (j * WMAPSC),
						Y_OFS + (li * endj) + (i * WMAPSC), 0x0000FFFF);
			}
			j++;
		}
		i++;
	}
}
