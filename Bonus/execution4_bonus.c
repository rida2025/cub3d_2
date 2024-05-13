/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:35:14 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/13 18:35:37 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_render_the_game(t_map *map)
{
	mlx_clear_window(map->mlx, map->win);
	put_map(map);
	put_minimap(map);
	put_weapon(map);
	return (0);
}

void	draw_minimap_line(t_map *map, double x, double y)
{
	double	dx;
	double	dy;
	double	fx;
	double	fy;
	int		line;

	dx = x - 100;
	dy = y - 100;
	fx = 100;
	fy = 100;
	if (fabs(dx) > fabs(dy))
		line = fabs(dx);
	else
		line = fabs(dy);
	dx = (double)dx / (double)line;
	dy = (double)dy / (double)line;
	while (line > 0)
	{
		my_mlx_m_pixel_put(&map->img, fx, fy, RED);
		fx += dx;
		fy += dy;
		line--;
	}
}

void	calc_minimap_line(t_map *map)
{
	double	x;
	double	y;

	x = 100;
	y = 100;
	x += (cos(map->angle) * 20);
	y += (sin(map->angle) * 20);
	draw_minimap_line(map, x, y);
}

void	put_player(t_map *info)
{
	int	i;
	int	j;

	i = 96;
	j = 96;
	while (i < 104)
	{
		while (j < 104)
		{
			my_mlx_m_pixel_put(&info->img, j, i, RED);
			j++;
		}
		j = 96;
		i++;
	}
	calc_minimap_line(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int	is_wall(t_map *map, int lenx, int leny)
{
	int	x;
	int	y;

	x = floor(lenx / 16);
	y = floor(leny / 16);
	if (y < 0 || y >= (map->my)
		|| x < 0 || x >= (map->mx))
		return (0);
	if (map->map[y][x] == '1')
		return (1);
	if (map->map[y][x] == 'D')
		return (2);
	if (map->map[y][x] == 'O')
		return (3);
	return (0);
}
