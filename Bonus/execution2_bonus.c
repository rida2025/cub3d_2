/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:33:37 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/13 18:34:21 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_calc_right_angle(t_map *map)
{
	double	x;
	double	y;

	x = map->player_x + (cos(map->angle + (M_PI / 2)) * map->move_speed);
	y = map->player_y + (sin(map->angle + (M_PI / 2)) * map->move_speed);
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

void	ft_calc_left_angle(t_map *map)
{
	double	x;
	double	y;

	x = map->player_x + (cos(map->angle - (M_PI / 2)) * map->move_speed);
	y = map->player_y + (sin(map->angle - (M_PI / 2)) * map->move_speed);
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

int	ft_mouse_rotation(int x, int y, t_map *map)
{
	int		tmp;
	double	helper;

	tmp = map->mouse_x;
	helper = 0;
	if (map->focus_mode == 0)
	{
		mlx_mouse_hide();
		if (x > SCREEN_WIDTH || x < 0 || y > SCREEN_HEIGHT || y < 0)
		{
			mlx_mouse_move(map->win, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
			map->mouse_x = (SCREEN_WIDTH / 2);
			map->mouse_y = (SCREEN_HEIGHT / 2);
		}
		else if (x != map->mouse_x)
		{
			helper = x - map->mouse_x;
			map->angle += helper * 0.0007f;
			map->mouse_x = x;
			map->drawzy = 1;
		}
	}
	else
		mlx_mouse_show();
	return (0);
}

int	mouse_click_hook(int keycode, int x, int y, t_map *map)
{
	(void)x;
	(void)y;
	if (keycode == 1)
	{
		map->click = 1;
		map->drawzy = 1;
	}
	return (0);
}
