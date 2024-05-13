/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:21:44 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/13 17:24:06 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_update(t_map *map)
{
	if (map->move_right == 1)
		ft_calc_right(map);
	if (map->move_left == 1)
		ft_calc_left(map);
	if (map->move_up == 1)
		ft_calc_front(map);
	if (map->move_down == 1)
		ft_calc_back(map);
	if (map->move_right_angle == 1)
		ft_calc_right_angle(map);
	if (map->move_left_angle == 1)
		ft_calc_left_angle(map);
	if (map->drawzy)
	{
		map->drawzy = 0;
		ft_render_the_game(map);
	}
	return (0);
}

void	ft_calc_left_angle(t_map *map)
{
	double	x;
	double	y;

	x = map->player_x + (cos(map->angle - (M_PI / 2)) * map->move_speed);
	y = map->player_y + (sin(map->angle - (M_PI / 2)) * map->move_speed);
	if (map->map[(int)floor((y + 4) / 32)][(int)floor(x / 32)] == '1')
		return ;
	if (map->map[(int)floor((y - 4) / 32)][(int)floor(x / 32)] == '1')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x + 4) / 32)] == '1')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x - 4) / 32)] == '1')
		return ;
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}

void	ft_calc_right_angle(t_map *map)
{
	double	x;
	double	y;

	x = map->player_x + (cos(map->angle + (M_PI / 2)) * map->move_speed);
	y = map->player_y + (sin(map->angle + (M_PI / 2)) * map->move_speed);
	if (map->map[(int)floor((y + 4) / 32)][(int)floor(x / 32)] == '1')
		return ;
	if (map->map[(int)floor((y - 4) / 32)][(int)floor(x / 32)] == '1')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x + 4) / 32)] == '1')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x - 4) / 32)] == '1')
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
	if (map->map[(int)floor((y + 4) / 32)][(int)floor(x / 32)] == '1')
		return ;
	if (map->map[(int)floor((y - 4) / 32)][(int)floor(x / 32)] == '1')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x + 4) / 32)] == '1')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x - 4) / 32)] == '1')
		return ;
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}

void	ft_calc_front(t_map *map)
{
	double	x;
	double	y;

	x = map->player_x + (cos(map->angle) * map->move_speed);
	y = map->player_y + (sin(map->angle) * map->move_speed);
	if (map->map[(int)floor((y + 4) / 32)][(int)floor(x / 32)] == '1')
		return ;
	if (map->map[(int)floor((y - 4) / 32)][(int)floor(x / 32)] == '1')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x + 4) / 32)] == '1')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x - 4) / 32)] == '1')
		return ;
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}
