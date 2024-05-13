/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:51:11 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/13 18:37:58 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_wall2(t_map *map, double horizontal_x, double horizontal_y)
{
	int	x;
	int	y;

	x = floor(horizontal_x / 32);
	y = floor(horizontal_y / 32);
	if (y < 0 || y >= (map->my)
		|| x < 0 || x >= (map->mx))
		return (0);
	if (map->map[y][x] == '1')
		return (1);
	if (map->map[y][x] == 'D')
		return (2);
	return (0);
}

int	is_what(t_map *map, double horizontal_x, double horizontal_y)
{
	int	x;
	int	y;

	x = floor(horizontal_x / 32);
	y = floor(horizontal_y / 32);
	if (y < 0 || y >= (map->my)
		|| x < 0 || x >= (map->mx))
		return (0);
	if (map->map[y][x] == 'D')
		return (2);
	if (map->map[y][x] == 'O')
		return (3);
	return (0);
}

void	horizontal_helper(t_map *map, double ray_angle)
{
	map->intercept_y = floor(map->player_y / 32) * 32;
	if (map->dawn)
		map->intercept_y += 32;
	map->intercept_x = map->player_x \
	+ (map->intercept_y - map->player_y) / tan(ray_angle);
	map->ystep = 32;
	if (map->up)
		map->ystep *= -1;
	map->xstep = 32 / tan(ray_angle);
	if (map->left && map->xstep > 0)
		map->xstep *= -1;
	if (map->right && map->xstep < 0)
		map->xstep *= -1;
	map->horizontal = 0;
}

int	execution(t_map map)
{
	map.img.img = mlx_new_image(map.mlx, map.width, map.height);
	mlx_hook(map.win, 17, 0, &close_window, &map);
	map.img.addr = mlx_get_data_addr(map.img.img,
			&map.img.bits_per_m_pixel, &map.img.line_length,
			&map.img.endian);
	mlx_mouse_hide();
	mlx_mouse_move(map.win, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	mlx_mouse_get_pos(map.win, &map.mouse_x, &map.mouse_y);
	mlx_hook(map.win, 2, 0, key_hook1, &map);
	mlx_hook(map.win, 3, 0, key_hook2, &map);
	mlx_hook(map.win, 6, 0, ft_mouse_rotation, &map);
	mlx_mouse_hook(map.win, mouse_click_hook, &map);
	mlx_loop_hook(map.mlx, ft_update, &map);
	mlx_loop(map.mlx);
	return (0);
}
