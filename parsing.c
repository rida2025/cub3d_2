/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:16:41 by mel-jira          #+#    #+#             */
/*   Updated: 2024/04/29 13:31:20 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_important_values(t_map *info, int i, int j)
{
	char	x;

	x = 'A';
	info->height = 1500;
	info->width = 1000;
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
}

void	set_important_values2(t_map *map)
{
	map->rot_speed = 1 *  (M_PI / 180);
	map->fov = 60 * (M_PI / 180);
	map->num_rays = SCREEN_HEIGHT;
	map->move_speed = 5;
	map->move_up = 0;
	map->move_down = 0;
	map->move_right = 0;
	map->move_left = 0;
	map->move_right_angle = 0;
	map->move_left_angle = 0;
	map->drawzy = 1;
}

int	parsing(t_map *map, char *map_name)
{
	if (check_name(map_name))
		return (error5(), 1);
	if (check_map(map, map_name))
		return (1);
	set_important_values(map, 0, 0);
	set_angle(map);
	set_important_values2(map);
	return (0);
}
