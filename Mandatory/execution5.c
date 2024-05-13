/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:25:41 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/13 17:26:00 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vertical(t_map *map, double ray_angle)
{
	double	vertical_x;
	double	vertical_y;

	vertical_helper(map, ray_angle);
	vertical_y = map->intercept_y;
	vertical_x = map->intercept_x;
	while (vertical_y >= 0 && vertical_x >= 0
		&& vertical_x <= ((map->mx - 2) * 32)
		&& vertical_y <= ((map->my - 2) * 32))
	{
		if (is_wall2(map, (vertical_x - map->left), vertical_y))
		{
			map->vertical_x = vertical_x;
			map->vertical_y = vertical_y;
			map->vertical = 1;
			return ;
		}
		vertical_x += map->xstep;
		vertical_y += map->ystep;
	}
	map->vertical_x = LONG_MAX;
	map->vertical_y = LONG_MAX;
}

void	reset(t_map *map, double ray_angle)
{
	map->right = 0;
	map->up = 0;
	map->left = 0;
	map->dawn = 0;
	if (ray_angle > 0 && ray_angle < M_PI)
		map->dawn = 1;
	if (!map->dawn)
		map->up = 1;
	if (ray_angle < (M_PI / 2) || ray_angle > (3 * M_PI) / 2)
		map->right = 1;
	if (!map->right)
		map->left = 1;
}

double	distance_finder(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

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
		map->hitx = map->horizontal_x;
		map->hity = map->horizontal_y;
		map->distance = horizontal_distance;
		map->horizontalhit = 1;
	}
	else
	{
		map->hitx = map->vertical_x;
		map->hity = map->vertical_y;
		map->distance = vertical_distance;
		map->verticalhit = 1;
	}
}
