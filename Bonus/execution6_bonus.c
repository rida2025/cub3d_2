/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution6_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:36:36 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/13 18:37:00 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	find_helper(t_map *map, double *hori_dis, double *vert_dis)
{
	if (map->horizontal)
		*hori_dis = distance_finder(map->player_x, \
		map->player_y, map->horizontal_x, map->horizontal_y);
	if (!map->horizontal)
		*hori_dis = LONG_MAX;
	if (map->vertical)
		*vert_dis = distance_finder(map->player_x, \
		map->player_y, map->vertical_x, map->vertical_y);
	if (!map->vertical)
		*vert_dis = LONG_MAX;
}

void	find_shortest(t_map *map)
{
	double	horizontal_distance;
	double	vertical_distance;

	horizontal_distance = 0;
	vertical_distance = 0;
	map->horizontalhit = 0;
	map->verticalhit = 0;
	find_helper(map, &horizontal_distance, &vertical_distance);
	if (horizontal_distance < vertical_distance)
	{
		map->door = map->doorh;
		map->hitx = map->horizontal_x;
		map->hity = map->horizontal_y;
		map->distance = horizontal_distance;
		map->horizontalhit = 1;
	}
	else
	{
		map->door = map->doorv;
		map->hitx = map->vertical_x;
		map->hity = map->vertical_y;
		map->distance = vertical_distance;
		map->verticalhit = 1;
	}
}

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
	if (map->door == 2)
		img = &map->door_texture;
	else if (map->verticalhit)
	{
		if (ray_angle > (M_PI / 2) && ray_angle < (3 * M_PI) / 2)
			img = &map->we_txture;
		else
			img = &map->es_txture;
	}
	else if (map->horizontalhit)
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			img = &map->so_txture;
		else
			img = &map->no_txture;
	}
	map->door = 0;
	map->doorh = 0;
	map->doorv = 0;
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
