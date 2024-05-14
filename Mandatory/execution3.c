/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:24:25 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/14 17:43:01 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_map(t_map *map)
{
	int		column;
	double	rayangle;

	column = 0;
	rayangle = map->angle - (map->fov / 2);
	while (column < map->num_rays)
	{
		ray_casting(map, column, rayangle);
		rayangle += map->fov / map->num_rays;
		column++;
	}
}

double	normlize(double rayangle)
{
	rayangle = fmod(rayangle, (2 * M_PI));
	if (rayangle < 0)
		rayangle += 2 * M_PI;
	return (rayangle);
}

int	ft_render_the_game(t_map *map)
{
	mlx_clear_window(map->mlx, map->win);
	put_map(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	return (0);
}

void	ft_calc_right(t_map *map)
{
	map->angle += 1 * (M_PI / 180);
	map->drawzy = 1;
}

void	ft_calc_left(t_map *map)
{
	map->angle -= 1 * (M_PI / 180);
	map->drawzy = 1;
}
