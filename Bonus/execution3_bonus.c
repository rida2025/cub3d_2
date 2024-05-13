/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:34:31 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/13 18:34:51 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_minimap(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	calc_minimap(map);
	while (y < 200)
	{
		while (x < 200)
		{
			if (is_wall(map, ((map->pos_x) + x), (map->pos_y) + y) == 2)
				my_mlx_m_pixel_put(&map->img, x, y, BLUE);
			else if (is_wall(map, ((map->pos_x) + x), (map->pos_y + y)) == 3)
				my_mlx_m_pixel_put(&map->img, x, y, GREEN);
			else if (is_wall(map, ((map->pos_x) + x), (map->pos_y + y)))
				my_mlx_m_pixel_put(&map->img, x, y, BLACK);
			else
				my_mlx_m_pixel_put(&map->img, x, y, WHITE);
			x++;
		}
		x = 0;
		y++;
	}
	put_player(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
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

void	ft_calc_front(t_map *map)
{
	double	x;
	double	y;

	x = map->player_x + (cos(map->angle) * map->move_speed);
	y = map->player_y + (sin(map->angle) * map->move_speed);
	if (map->map[(int)floor((y + 4) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y + 4) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor((y - 4) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y - 4) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x + 4) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x + 4) / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x - 4) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x - 4) / 32)] == 'D')
		return ;
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}

void	ft_calc_back(t_map *map)
{
	double	x;
	double	y;

	x = map->player_x - (cos(map->angle) * map->move_speed);
	y = map->player_y - (sin(map->angle) * map->move_speed);
	if (map->map[(int)floor((y + 4) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y + 4) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor((y - 4) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y - 4) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x + 4) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x + 4) / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x - 4) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x - 4) / 32)] == 'D')
		return ;
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}
