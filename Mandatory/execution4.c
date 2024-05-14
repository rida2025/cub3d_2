/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:25:06 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/14 18:12:01 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rendering_helper(t_map *map, int *top, int *bottom, double ray_angle)
{
	map->true_distance = map->distance * cos(ray_angle - map->angle);
	map->obj_distance = (double)(SCREEN_WIDTH / 2) / tan(map->fov / 2);
	map->obj_height = (32 / map->true_distance) * map->obj_distance;
	*top = (double)(SCREEN_HEIGHT / 2) - (double)(map->obj_height / 2);
	*bottom = (double)(SCREEN_HEIGHT / 2) + (double)(map->obj_height / 2);
}

t_data	*img_found(t_map *map, double ray_angle)
{
	t_data	*img;

	img = NULL;
	if (map->verticalhit)
	{
		if (ray_angle > M_PI / 2 && ray_angle < (3 * M_PI) / 2)
			img = &map->we_txture;
		else
			img = &map->es_txture;
	}
	if (map->horizontalhit)
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			img = &map->so_txture;
		else
			img = &map->no_txture;
	}
	return (img);
}

void	img_helper(t_map *map, t_data *img)
{
	if (map->verticalhit)
		map->offset_x = (int)map->hity % 32;
	else
		map->offset_x = (int)map->hitx % 32;
	map->offset_x *= img->line_width / 32;
	map->buffer = (unsigned int *)img->addr;
}

void	rendering(t_map *map, int column, double ray_angle)
{
	int		i;
	int		top;
	int		bottom;
	double	foctor;
	t_data	*img;

	i = 0;
	top = 0;
	bottom = 0;
	rendering_helper(map, &top, &bottom, ray_angle);
	img = img_found(map, ray_angle);
	img_helper(map, img);
	while (i < top)
		my_mlx_m_pixel_put(&map->img, column, i++, map->ceiling_color);
	foctor = img->line_heigth / map->obj_height;
	while (i < bottom && i < SCREEN_HEIGHT)
	{
		map->offset_y = (i - top) * foctor;
		my_mlx_m_pixel_put(&map->img, column, i++, \
		map->buffer[(map->offset_y * img->line_width) + map->offset_x]);
	}
	while (i < SCREEN_HEIGHT)
		my_mlx_m_pixel_put(&map->img, column, i++, map->floor_color);
}

void	ray_casting(t_map *map, int column, double ray_angle)
{
	ray_angle = normlize(ray_angle);
	reset(map, ray_angle);
	horizontal(map, ray_angle);
	vertical(map, ray_angle);
	find_shortest(map);
	rendering(map, column, ray_angle);
}
