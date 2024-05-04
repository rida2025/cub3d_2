/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:51:11 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/04 16:31:36 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_now(t_map *map, int y, int x)
{
	int i;
	int	j;
	
	i = 0;
	j = 0;
	while (i < 31)
	{
		// puts("Wi");
		while (j < 31)
		{
			// puts("Wj");
			my_mlx_M_PIxel_put(&map->img, (j+x), (i+y), BLACK);
			j++;
		}
		j  = 0;
		i++;
	}
}

void	draw_floor_now(t_map *map, int y, int x)
{
	int i;
	int	j;
	
	i = 0;
	j = 0;
	while (i < 31)
	{
		// puts("Fi");
		while (j < 31)
		{
			// puts("Fj");
			my_mlx_M_PIxel_put(&map->img, (j+x), (i+y), WHITE);
			j++;
		}
		j  = 0;
		i++;
	}
}

void	put_player_inmap(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 8)
	{
		// puts("Pi");
		while (j < 8)
		{
			// puts("Pj");
			my_mlx_M_PIxel_put(&map->img, ((32*map->player_x)+j), ((32*map->player_y)+i), RED);
			j++;
		}
		j = 96;
		i++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
}

void	put_map(t_map *map)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = 200;
	y = 200;
	i = 1;
	j = 1;
	printf("my=[%f], mx=[%f]\n", map->my, map->mx);
	while (i < (int)(map->my - 1))
	{
		// puts("1i");
		while (j < (int)(map->mx - 1))
		{
			// puts("1j");
			if (map->map[i][j] == '1')
				draw_wall_now(map, 200+(i*32), 200+(j*32));
			else
				draw_floor_now(map, 200+(i*32), 200+(j*32));
			j++;
		}
		j = 1;
		i++;
	}	
	// put_player_inmap(map);
}

double    normlize(double rayangle)
{
    rayangle = fmod(rayangle, (2 * M_PI));
    if (rayangle < 0)
        rayangle += 2 * M_PI;
    return (rayangle);
}

void	put_background(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < SCREEN_HEIGHT)
	{
		while (j < SCREEN_WIDTH)
		{
			my_mlx_M_PIxel_put(&map->img, j, i, BACKGROUND);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
}

int	ft_render_the_game(t_map *map)
{
	mlx_clear_window(map->mlx, map->win);
	map->angle = normlize(map->angle);
	put_background(map);
	put_map(map);
	// puts("ok");
	// exit(1);
	put_minimap(map);
	return (0);
}

void	draw_minimap_line(t_map *map, double x, double y)
{
	int		dx = 0;
	int		dy = 0;
	double	fx = 0;
	double	fy = 0;
	int		line;
	double	lx;
	double	ly;
	
	dx = x - 100;
	dy = y - 100;

	if (abs(dx) > abs(dy))
		line = abs(dx);
	else
		line = abs(dy);
	lx = (double)dx / (double)line;
	ly = (double)dy / (double)line;
	
	fx = 100;
	fy = 100;
	printf("before dx=[%d], dy=[%d]\n", dx, dy);
	int i = 0;
	while (i <= line)
	{
		my_mlx_M_PIxel_put(&map->img, fx, fy, RED);
		fx += lx;
		fy += ly;
		i++;
	}
	printf("after dx=[%d], dy=[%d]\n", dx, dy);
}

void	calc_minimap_line(t_map *map)
{
	double	x;
	double	y;

	x = 100;
	y = 100;
	x += (cos(map->angle) * 20);
	y += (sin(map->angle) * 20);
	printf("%f x=[%f] y=[%f] ******\n", map->angle, x,y);
	draw_minimap_line(map, x, y);
}


void	put_player(t_map *info)
{
	int	i;
	int	j;

	i = 96;
	j = 96;
	while (i < 104)
	{
		while (j < 104)
		{
			my_mlx_M_PIxel_put(&info->img, j, i, RED);
			j++;
		}
		j = 96;
		i++;
	}
	calc_minimap_line(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int	is_wall(t_map *info, int lenx, int leny)
{
	int	x;
	int	y;

	x = floor(lenx / 16);
	y = floor(leny / 16);
	if (y < 0 || y >= (info->my)
		|| x < 0 || x >= (info->mx))
		return (0);
	if (info->map[y][x] == '1')
		return (1);
	return (0);
}

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
			if (is_wall(map, ((map->position_x) + x), ((map->position_y) + y)))
				my_mlx_M_PIxel_put(&map->img, x, y, BLACK);
			else
				my_mlx_M_PIxel_put(&map->img, x, y, WHITE);
			x++;
		}
		x = 0;
		y++;
	}
	put_player(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	return ;
}

void	ft_calc_right(t_map *map)
{
	puts("move right");
	map->angle += 1 * (M_PI / 180);
	map->drawzy = 1;
}

void	ft_calc_left(t_map *map)
{
	puts("move left");
	map->angle -= 1 * (M_PI / 180);
	map->drawzy = 1;
}

void	ft_calc_front(t_map *map)
{
	puts("move front");
	double x;
	double y;
	x = map->player_x + (cos(map->angle) * map->move_speed);
	y = map->player_y + (sin(map->angle) * map->move_speed);
	if (map->map[(int)floor(y / 32)][(int)floor(x / 32)] == '1')
	{
		puts("is wall");
		return ;
	}
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}

void	ft_calc_back(t_map *map)
{
	puts("move back");
	double x;
	double y;
	x = map->player_x - (cos(map->angle) * map->move_speed);
	y = map->player_y - (sin(map->angle) * map->move_speed);
	if (map->map[(int)floor(y / 32)][(int)floor(x / 32)] == '1')
		return ;
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}

void	ft_calc_right_angle(t_map *map)
{
	puts("move front right");
	double x;
	double y;
	x = map->player_x + (cos(map->angle + (M_PI / 2)) * map->move_speed);
	y = map->player_y + (sin(map->angle + (M_PI / 2)) * map->move_speed);
	if (map->map[(int)floor(y / 32)][(int)floor(x / 32)] == '1')
		return ;
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}

void	ft_calc_left_angle(t_map *map)
{
	puts("move front left");
	double x;
	double y;
	x = map->player_x + (cos(map->angle - (M_PI / 2)) * map->move_speed);
	y = map->player_y + (sin(map->angle - (M_PI / 2)) * map->move_speed);
	if (map->map[(int)floor(y / 32)][(int)floor(x / 32)] == '1')
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
		puts("entered");
		map->drawzy = 0;
		ft_render_the_game(map);
	}
	return (0);
}

int	execution(t_map map)
{
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, map.width, map.height, "cub3D");
	map.img.img = mlx_new_image(map.mlx, map.width, map.height);
	mlx_hook(map.win, 17, 0, &close_window, &map);
	map.img.addr = mlx_get_data_addr(map.img.img,
			&map.img.bits_per_M_PIxel, &map.img.line_length,
			&map.img.endian);
	print_map(map.map);
	mlx_hook(map.win, 2, 0, key_hook1, &map);
	mlx_hook(map.win, 3, 0, key_hook2, &map);
	mlx_loop_hook(map.mlx, ft_update, &map);
	mlx_loop(map.mlx);
	return (0);
}
