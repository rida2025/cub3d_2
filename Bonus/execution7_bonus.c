/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution7_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:37:20 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/13 18:37:46 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	horizontal(t_map *map, double ray_angle)
{
	double	horizontal_x;
	double	horizontal_y;

	horizontal_helper(map, ray_angle);
	horizontal_y = map->intercept_y;
	horizontal_x = map->intercept_x;
	while (horizontal_y >= 0 && horizontal_x >= 0
		&& horizontal_x <= ((map->mx) * 32) && horizontal_y <= ((map->my) * 32))
	{
		if (is_wall2(map, horizontal_x, (horizontal_y - map->up)))
		{
			map->doorh = is_what(map, horizontal_x, (horizontal_y - map->up));
			map->horizontal_x = horizontal_x;
			map->horizontal_y = horizontal_y;
			map->horizontal = 1;
			return ;
		}
		horizontal_x += map->xstep;
		horizontal_y += map->ystep;
	}
}

void	vertical_helper(t_map *map, double ray_angle)
{
	map->intercept_x = floor(map->player_x / 32) * 32;
	if (map->right)
		map->intercept_x += 32;
	map->intercept_y = map->player_y \
	+ (map->intercept_x - map->player_x) * tan(ray_angle);
	map->xstep = 32;
	if (map->left)
		map->xstep *= -1;
	map->ystep = 32 * tan(ray_angle);
	if (map->up && map->ystep > 0)
		map->ystep *= -1;
	if (map->dawn && map->ystep < 0)
		map->ystep *= -1;
	map->vertical = 0;
}

void	vertical(t_map *map, double ray_angle)
{
	double	vertical_x;
	double	vertical_y;

	vertical_helper(map, ray_angle);
	vertical_y = map->intercept_y;
	vertical_x = map->intercept_x;
	while (vertical_y >= 0 && vertical_x >= 0
		&& vertical_x <= ((map->mx) * 32) && vertical_y <= ((map->my) * 32))
	{
		if (is_wall2(map, (vertical_x - map->left), vertical_y))
		{
			map->doorv = is_what(map, (vertical_x - map->left), vertical_y);
			map->vertical_x = vertical_x;
			map->vertical_y = vertical_y;
			map->vertical = 1;
			return ;
		}
		vertical_x += map->xstep;
		vertical_y += map->ystep;
	}
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
