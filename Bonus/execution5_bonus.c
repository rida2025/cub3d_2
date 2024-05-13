/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution5_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:35:58 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/13 18:36:22 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	put_weapon(t_map *map)
{
	if (map->click)
	{
		if (map->i < 15)
		{
			mlx_put_image_to_window(map->mlx, map->win, \
			map->ptr.image[map->i], SCREEN_WIDTH / 2, SCREEN_HEIGHT - 250);
			map->i++;
			map->drawzy = 1;
		}
		else
		{
			map->i = 0;
			map->click = 0;
		}
	}
	mlx_put_image_to_window(map->mlx, map->win, \
	map->ptr.image[map->i], SCREEN_WIDTH / 2, SCREEN_HEIGHT - 250);
}
