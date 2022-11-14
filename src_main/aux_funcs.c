#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_pixel(t_data *p_img, int x, int y, t_color color)
{
	int	i;

	(void)color;
	i = (x * p_img->bits_per_pixel / 8)
		+ (y * p_img->line_length);
//	p_img->addr[i] = color.channel[3];
//	p_img->addr[++i] = color.channel[2];
//	p_img->addr[++i] = color.channel[1];
//	p_img->addr[++i] = color.channel[0];
	p_img->addr[i] = 0xFF;
	p_img->addr[++i] = 0xFF;
	p_img->addr[++i] = 0x00;
	p_img->addr[++i] = 0x00;
//	p_img->addr[i] = 0x00FFFF;
}

int	close_win(t_vars *p_vars)
{
	mlx_destroy_window(p_vars->mlx, p_vars->win);
	exit (0);
}
