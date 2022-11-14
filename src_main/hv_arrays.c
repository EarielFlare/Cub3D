#include "cub3d.h"

void	measure_map(t_vars *p_vars)
{
	int	maxlen;

	maxlen = 0;
	p_vars->map_sizei = 0;
	while(p_vars->map[p_vars->map_sizei]){
		if (ft_strlen(p_vars->map[p_vars->map_sizei]) > (size_t)maxlen)
			maxlen = ft_strlen(p_vars->map[p_vars->map_sizei]);
		p_vars->map_sizei++;
	}
	p_vars->map_sizej = maxlen;	
	printf("map_sizei: %d\n", p_vars->map_sizei);
	printf("map_sizej: %d\n", p_vars->map_sizej);
	find_size_max(p_vars);
	printf("map_size_min: %d\n", p_vars->map_size_max);
}

void	find_size_max(t_vars *p_vars)
{
	p_vars->map_size_max = p_vars->map_sizei;
	if (p_vars->map_sizej > p_vars->map_sizei)
		p_vars->map_size_max = p_vars->map_sizej;
}

char	**make_array(t_vars *p_vars, int endi, int endj)
{
	int		cnt;
	char	**array;

	array = (char **)ft_calloc(p_vars->map_sizei + endi, sizeof(char *));
	cnt = 0;
	while(cnt < p_vars->map_sizei + endi){
		array[cnt] = (char *)ft_calloc(p_vars->map_sizej + endj, sizeof(char));
		cnt++;
	}
	return (array);
}

void	free_array(t_vars *p_vars, char **array, int endi)
{
	int		cnt;

	cnt = 0;
	while(cnt < p_vars->map_sizei + endi){
		free(array[cnt]);
		cnt++;
	}
	free(array);
}

void	fill_with_sp(t_vars *p_vars, char **array, int endi, int endj)
{
	int	i;
	int	j;
	
	i = 0;
	while(i < p_vars->map_sizei + endi)
	{
		j = 0;		
		while(j < p_vars->map_sizej + endj){
			array[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void	fill_with_val(t_vars *p_vars)
{
	int	i;
	int	j;
	
	i = 0;
	while(p_vars->map[i]){
		j = 0;
		while(p_vars->map[i][j]){
			if (p_vars->map[i][j] == '1')
			{
				if (p_vars->horz_walls[i][j] == '-')
					p_vars->horz_walls[i][j] = ' ';
				else
					p_vars->horz_walls[i][j] = '-';
				p_vars->horz_walls[i + 1][j] = '-';
				if (p_vars->vert_walls[i][j] == '|')
					p_vars->vert_walls[i][j] = ' ';
				else
					p_vars->vert_walls[i][j] = '|';
				p_vars->vert_walls[i][j + 1] = '|';
			}
			j++;
		}
		i++;
	}
}

void	print_array(t_vars *p_vars)
{
	int	i;
	int	j;

	i = 0;
	while(i < p_vars->map_sizei + 1){
		j = 0;
		while(j < p_vars->map_sizej){
			write(1, &p_vars->horz_walls[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	i = 0;
	while(i < p_vars->map_sizei){
		j = 0;
		while(j < p_vars->map_sizej + 1){
			write(1, &p_vars->vert_walls[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
