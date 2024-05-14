/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utilitis_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:24:41 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/14 15:52:34 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	close_window(t_map *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

void	my_mlx_m_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + ((y * data->line_length) \
	+ (x * (data->bits_per_m_pixel / 8)));
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		*(unsigned int *)dst = color;
}

void	open_or_close(t_map *map)
{
	int	x;
	int	y;

	x = floor(map->player_x + (cos(map->angle) * 16)) / 32;
	y = floor(map->player_y + (sin(map->angle) * 16)) / 32;
	if (map->map[y][x] == 'D')
		map->map[y][x] = 'O';
	else if (map->map[y][x] == 'O')
	{
		if (!((int)(map->player_y / 32) == y \
		&& (int)(map->player_x / 32) == x))
			map->map[y][x] = 'D';
	}
	map->drawzy = 1;
}

int	key_hook1(int keycode, t_map *map)
{
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(0);
	}
	else if (keycode == 13 || keycode == 126)
		map->move_up = 1;
	else if (keycode == 1 || keycode == 125)
		map->move_down = 1;
	else if (keycode == 124)
		map->move_right = 1;
	else if (keycode == 123)
		map->move_left = 1;
	else if (keycode == 2)
		map->move_right_angle = 1;
	else if (keycode == 0)
		map->move_left_angle = 1;
	else if (keycode == 3 && map->focus_mode == 0)
		map->focus_mode = 1;
	else if (keycode == 3 && map->focus_mode == 1)
		map->focus_mode = 0;
	else if (keycode == 14)
		open_or_close(map);
	return (0);
}
