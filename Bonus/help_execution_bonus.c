/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execution_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:38:32 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/13 18:40:01 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	calc_minimap(t_map *map)
{
	map->mini_x = map->player_x / 32;
	map->mini_y = map->player_y / 32;
	map->mini_x *= 16;
	map->mini_y *= 16;
	map->pos_x = map->mini_x - 100;
	map->pos_y = map->mini_y - 100;
}

void	set_texture(t_map *map)
{
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->width, map->height, "cub3D");
	map->no_txture.img = mlx_xpm_file_to_image(map->mlx, map->north_path, \
	&map->no_txture.line_width, &map->no_txture.line_heigth);
	map->no_txture.addr = mlx_get_data_addr(map->no_txture.img, \
	&map->no_txture.bits_per_m_pixel, \
	&map->no_txture.line_length, &map->no_txture.endian);
	map->so_txture.img = mlx_xpm_file_to_image(map->mlx, map->south_path, \
	&map->so_txture.line_width, &map->so_txture.line_heigth);
	map->so_txture.addr = mlx_get_data_addr(map->so_txture.img, \
	&map->so_txture.bits_per_m_pixel, &map->so_txture.line_length, \
	&map->so_txture.endian);
	map->we_txture.img = mlx_xpm_file_to_image(map->mlx, map->west_path, \
	&map->we_txture.line_width, &map->we_txture.line_heigth);
	map->we_txture.addr = mlx_get_data_addr(map->we_txture.img, \
	&map->we_txture.bits_per_m_pixel, \
	&map->we_txture.line_length, &map->we_txture.endian);
	map->es_txture.img = mlx_xpm_file_to_image(map->mlx, map->east_path, \
	&map->es_txture.line_width, &map->es_txture.line_heigth);
	map->es_txture.addr = mlx_get_data_addr(map->es_txture.img, \
	&map->es_txture.bits_per_m_pixel, &map->es_txture.line_length, \
	&map->es_txture.endian);
	help_set_texture(map);
}

int	parsing(t_map *map, char *map_name)
{
	if (check_name(map_name))
		return (error5(), 1);
	if (check_map(map, map_name))
		return (1);
	set_important_values(map, 0, 0);
	set_angle(map);
	set_texture(map);
	set_important_values2(map);
	map->floor_color = encode_rgb(map->floor[0], map->floor[1], map->floor[2]);
	map->ceiling_color = encode_rgb(map->ceiling[0], map->ceiling[1], \
	map->ceiling[2]);
	return (0);
}
