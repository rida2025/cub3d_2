/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utilitis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:24:41 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/14 18:10:11 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (0);
}

int	key_hook2(int keycode, t_map *map)
{
	if (keycode == 13 || keycode == 126)
		map->move_up = 0;
	else if (keycode == 1 || keycode == 125)
		map->move_down = 0;
	else if (keycode == 124)
		map->move_right = 0;
	else if (keycode == 123)
		map->move_left = 0;
	else if (keycode == 2)
		map->move_right_angle = 0;
	else if (keycode == 0)
		map->move_left_angle = 0;
	return (0);
}
