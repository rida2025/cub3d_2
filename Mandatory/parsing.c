/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:16:41 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/14 17:41:49 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_important_values(t_map *info, int i, int j)
{
	char	x;

	x = 'A';
	info->height = SCREEN_HEIGHT;
	info->width = SCREEN_WIDTH;
	while (info->map[i])
	{
		while (info->map[i][j])
		{
			x = info->map[i][j];
			if (x == 'N' || x == 'S' || x == 'E' || x == 'W')
			{
				info->player_x = (j + 0.5) * 32;
				info->player_y = (i + 0.5) * 32;
				info->direction = x;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	set_angle(t_map *map)
{
	if (map->direction == 'E')
		map->angle = 0.0;
	else if (map->direction == 'S')
		map->angle = M_PI / 2;
	else if (map->direction == 'W')
		map->angle = M_PI;
	else if (map->direction == 'N')
		map->angle = (M_PI * 3) / 2;
	map->rot_speed = 1 * (M_PI / 180);
	map->fov = 60 * (M_PI / 180);
	map->num_rays = SCREEN_WIDTH;
	map->move_speed = 5;
	map->move_up = 0;
	map->move_down = 0;
	map->move_right = 0;
	map->move_left = 0;
	map->move_right_angle = 0;
	map->move_left_angle = 0;
	map->drawzy = 1;
	map->right = 0;
	map->up = 0;
	map->left = 0;
	map->dawn = 0;
}

void	set_texture2(t_map *map)
{
	map->es_txture.img = mlx_xpm_file_to_image(map->mlx, map->east_path, \
	&map->es_txture.line_width, &map->es_txture.line_heigth);
	if (!map->es_txture.img)
		exit(1);
	map->es_txture.addr = mlx_get_data_addr(map->es_txture.img, \
	&map->es_txture.bits_per_m_pixel, \
	&map->es_txture.line_length, &map->es_txture.endian);
}

void	set_texture(t_map *map)
{
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->width, map->height, "cub3D");
	map->no_txture.img = mlx_xpm_file_to_image(map->mlx, map->north_path, \
	&map->no_txture.line_width, &map->no_txture.line_heigth);
	if (!map->no_txture.img)
		exit(1);
	map->no_txture.addr = mlx_get_data_addr(map->no_txture.img, \
	&map->no_txture.bits_per_m_pixel, &map->no_txture.line_length, \
	&map->no_txture.endian);
	map->so_txture.img = mlx_xpm_file_to_image(map->mlx, map->south_path, \
	&map->so_txture.line_width, &map->so_txture.line_heigth);
	if (!map->so_txture.img)
		exit(1);
	map->so_txture.addr = mlx_get_data_addr(map->so_txture.img, \
	&map->so_txture.bits_per_m_pixel, &map->so_txture.line_length, \
	&map->so_txture.endian);
	map->we_txture.img = mlx_xpm_file_to_image(map->mlx, map->west_path, \
	&map->we_txture.line_width, &map->we_txture.line_heigth);
	if (!map->we_txture.img)
		exit(1);
	map->we_txture.addr = mlx_get_data_addr(map->we_txture.img, \
	&map->we_txture.bits_per_m_pixel, &map->we_txture.line_length, \
	&map->we_txture.endian);
	set_texture2(map);
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
	map->floor_color = encode_rgb(map->floor[0], map->floor[1], map->floor[2]);
	map->ceiling_color = encode_rgb(map->ceiling[0], map->ceiling[1], \
	map->ceiling[2]);
	return (0);
}
