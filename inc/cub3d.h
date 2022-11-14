#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"

# include <stdio.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

# include <signal.h>
# include <sys/time.h>

# define WIDTH		960
# define HEIGHT		700
# define X_OFS		50
# define Y_OFS		50
# define WMAPSC		25

extern int		g_flag;

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_color
{
	unsigned char	channel[4];
}	t_color;

typedef struct s_complex
{
	double			re;
	double			im;
}	t_complex;

typedef struct s_point
{
	int				iter;
	t_color			color;
	t_color			color_last;
}	t_point;

typedef struct s_koefs
{
	t_complex		newv;
	t_complex		c_koef;
	t_complex		m_koef;
}	t_koefs;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				max_iter;
	double			zoom;
	int				mouse_x;
	int				mouse_y;
	double			x_step;
	double			y_step;
	int				move_speed;
	t_complex		ld_corner;
	t_complex		ru_corner;
	t_koefs			fractol;
	t_bool			is_fixed;
	t_bool			is_help;
	t_point			point;
	int				pq1;
	int				pq2;
	int				(*proc)(t_koefs *p_img, int max_iter);
	t_bool			btn2_down;
}	t_data;

typedef struct s_assets
{
	char		*floor;
	char		*ceiling;
	char		*north_wall;
	char		*south_wall;
	char		*east_wall;
	char		*west_wall;
}	t_assets;

typedef struct s_ray
{
	double		ray_dir;
	double		tanf_dir;
	double		b_ray;
	double		dist_horz;
	double		dist_vert;
	double		dist_min;
	double		sinf_dir;
	double		cosf_dir;
}	t_ray;

typedef struct s_pos
{
	double	x;
	int		x_restr[2];
	int		x_floor;
	int		x_ceil;
	double	y;
	int		y_restr[2];
	int		y_floor;
	int		y_ceil;
}	t_pos;

typedef struct s_player
{
	t_pos		pos;
	double		dir;
	double		fov;
	double		sinf_dir0;
	double		cosf_dir0;
	double		sinf_dir180;
	double		cosf_dir180;
	double		sinf_dir90;
	double		cosf_dir90;
	double		sinf_dir_90;
	double		cosf_dir_90;
	double		sinf_dir45;
	double		cosf_dir45;
	double		sinf_dir225;
	double		cosf_dir225;
	double		sinf_dir135;
	double		cosf_dir135;
	double		sinf_dir_45;
	double		cosf_dir_45;
	int			divider;
	int			sense;
	double		step;
	t_bool		forward;
	t_bool		backward;
	t_bool		leftward;
	t_bool		rightward;
}	t_player;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	int			x;
	int			y;
	t_data		img;
	int			count;
	char		**map;
	int			map_sizei;
	int			map_sizej;
	int			map_size_max;
	t_assets	assets;
	t_player	player;
	char		**horz_walls;
	char		**vert_walls;
	int			raynum;
	t_ray		ray[200];
	double		ray_step;
}	t_vars;

typedef struct s_proc
{
	char		*name;
	int			(*proc)(t_koefs *fractol, int max_iter);
}	t_proc;

void			init_program(t_vars *p_vars);
void			init_image(t_vars *p_vars);
void			set_defaults(t_vars *p_vars);
int				while_func(void *strct);
int				render_func(void *strct);
void			put_pixel(t_data *p_img, int x, int y, t_color color);
void			calc_image(t_data *p_img);
int				mouse_move(int x, int y, t_vars *p_vars);
int				mouse_hook_press(int keycode, int x, int y, t_vars *p_vars);
int				mouse_hook_release(int keycode, int x, int y, t_vars *p_vars);
int				key_hook_press(int keycode, t_vars *p_vars);
int				key_hook_release(int keycode, t_vars *p_vars);
int				close_win(t_vars *p_vars);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			print_prompt(void);
void			draw_help_1(t_vars *p_vars);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
void			ft_putendl(char *s);
void			ft_exit(char *err);
void			check_file(char *file, t_vars *p_vars);
void			check_file_argv(int fd, t_vars *p_vars);
void			create_map(t_vars *p_vars, char *str, int fd);
void			map_line_check(char *str);
int				its_not_map(t_vars *vars, char *str);
int				its_map_line(char *str);
int				dpl(char *arg);
char			**ft_free_split(char *split[]);
void			check_assets(t_vars *vars);
void			init_vars(t_vars *p_vars);
void			map_check(t_vars *p_vars);
void			small_map_check(t_vars *vars);
void			border_zero_check(t_vars *vars);
void			border_void_check(t_vars *vars, int i, int j);
void			check_we_ea_so_border(t_vars *vars, int *flag);
void			check_east_border(t_vars *vars, int *flag);
void			get_player_direction(char dir, t_vars *p_vars);
void			player_pos_check(t_vars *p_vars, int x, int y);
void			find_player_pos(t_vars *p_vars);
void			measure_map(t_vars *p_vars);
char			**make_array(t_vars *p_vars, int endi, int endj);
void			free_array(t_vars *p_vars, char **array, int endi);
void			fill_with_sp(t_vars *p_vars, char **array, int endi, int endj);
void			fill_with_val(t_vars *p_vars);
void			print_array(t_vars *p_vars);
void			calc_map(t_vars *p_vars, t_data *p_img);
void			calc_walls(t_vars *p_vars, t_data *p_img, char **array, int endi, int endj);
void			horz_check(t_vars *p_vars, t_data *p_img);
void			horz_inter_check(t_vars *p_vars, int iterator, int ray_cnt, int cnt_dir);
void			draw_ray(t_vars *p_vars, t_data *p_img);
void			vert_check(t_vars *p_vars, t_data *p_img);
void			vert_inter_check(t_vars *p_vars, int iterator, int ray_cnt, int cnt_dir);
void			rays_prep(t_vars *p_vars);
void			sincos_prep(t_vars *p_vars);
void			find_dist_min(t_vars *p_vars);
void			find_size_max(t_vars *p_vars);
void			kbrd_hook_check(t_vars *p_vars);
void			player_move(t_vars *p_vars, double sinf, double cosf);

#endif
