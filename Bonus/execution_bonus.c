/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:51:11 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/12 16:01:15 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_wall2(t_map *map, double horizontal_x, double horizontal_y)
{
	int	x;
	int	y;
	
	x = floor(horizontal_x / 32);
	y = floor(horizontal_y / 32);
	if (y < 0 || y >= (map->my)
		|| x < 0 || x >= (map->mx))
		return (0);
	if (map->map[y][x] == '1')
		return (1);
	if (map->map[y][x] == 'D')
		return (2);
	return (0);
}

int	is_what(t_map *map, double horizontal_x, double horizontal_y)
{
	int	x;
	int	y;
	
	x = floor(horizontal_x / 32);
	y = floor(horizontal_y / 32);
	if (y < 0 || y >= (map->my)
		|| x < 0 || x >= (map->mx))
		return (0);
	if (map->map[y][x] == 'D')
		return (2);
	if (map->map[y][x] == 'O')
		return (3);
	return (0);
}

void	horizontal_helper(t_map *map, double ray_angle)
{
	map->intercept_y = floor(map->player_y / 32) * 32;
	if (map->dawn)
		map->intercept_y += 32;
	map->intercept_x = map->player_x + (map->intercept_y - map->player_y) / tan(ray_angle);
	map->ystep = 32;
	if (map->up)
		map->ystep *= -1;
	map->xstep = 32 / tan(ray_angle);
	if (map->left && map->xstep > 0)
		map->xstep *= -1;
	if (map->right && map->xstep < 0)
		map->xstep *= -1;
	map->horizontal = 0;
}

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
			map->doorH = is_what(map, horizontal_x, (horizontal_y - map->up));
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
	map->intercept_y = map->player_y + (map->intercept_x - map->player_x) * tan(ray_angle);
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
			map->doorV = is_what(map, (vertical_x - map->left), vertical_y);
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
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2- y1) * (y2 - y1))));
}

void	find_helper(t_map *map, double *hori_dis, double *vert_dis)
{
	if (map->horizontal)
		*hori_dis = distance_finder(map->player_x,
			map->player_y, map->horizontal_x, map->horizontal_y);
	if (!map->horizontal)
		*hori_dis = LONG_MAX;
	if (map->vertical)
		*vert_dis = distance_finder(map->player_x,
			map->player_y, map->vertical_x, map->vertical_y);
	if (!map->vertical)
		*vert_dis = LONG_MAX;
}

void	find_shortest(t_map *map)
{
	double	horizontal_distance;
	double	vertical_distance;
	
	horizontal_distance = 0;
	vertical_distance  = 0;
	map->horizontalHit = 0;
	map->verticalHit = 0;
	find_helper(map, &horizontal_distance, &vertical_distance);
	if (horizontal_distance < vertical_distance)
	{
		map->door = map->doorH;
		map->Hitx = map->horizontal_x;
		map->Hity = map->horizontal_y;
		map->distance = horizontal_distance;
		map->horizontalHit = 1;
	}
	else
	{
		map->door = map->doorV;
		map->Hitx = map->vertical_x;
		map->Hity = map->vertical_y;
		map->distance = vertical_distance;
		map->verticalHit = 1;
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

t_data *img_found(t_map *map, double ray_angle)
{
	t_data	*img;

	img = NULL;
	if (map->door == 2)
		img = &map->door_texture;
	else if (map->verticalHit)
	{
		if (ray_angle > (M_PI / 2) && ray_angle < (3 * M_PI) / 2)
			img = &map->we_txture;
		else
			img = &map->es_txture;
	}
	else if (map->horizontalHit)
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			img = &map->so_txture;
		else
			img = &map->no_txture;
	}
	map->door = 0;
	map->doorH = 0;
	map->doorV = 0;
	return (img);
}

void	img_helper(t_map *map, t_data *img)
{
	if (map->verticalHit)
		map->offset_x = (int)map->Hity % 32;
	else
		map->offset_x = (int)map->Hitx % 32;
	map->offset_x *= img->line_width / 32;
	map->buffer = (unsigned int *)img->addr;
}

void	rendering(t_map *map, int column, double ray_angle)
{
	int i;
	int	top;
	int	bottom;
	double foctor;
	t_data	*img;

	i = 0;
	top = 0;
	bottom = 0;
	rendering_helper(map, &top, &bottom, ray_angle);
	img = img_found(map, ray_angle);
	img_helper(map, img);
	while (i < top)
		my_mlx_M_PIxel_put(&map->img, column, i++, map->ceiling_color);
	foctor = img->line_heigth / map->obj_height;
	while (i < bottom && i < SCREEN_HEIGHT)
	{
		map->offset_y = (i - top) * foctor;
		my_mlx_M_PIxel_put(&map->img, column, i++, map->buffer[(map->offset_y * img->line_width) + map->offset_x]);
	}
	while (i < SCREEN_HEIGHT)
		my_mlx_M_PIxel_put(&map->img, column, i++, map->floor_color);
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

double    normlize(double rayangle)
{
    rayangle = fmod(rayangle, (2 * M_PI));
    if (rayangle < 0)
        rayangle += 2 * M_PI;
    return (rayangle);
}

void	put_weapon(t_map *map)
{
	if (map->i > 15)
		map->i = 0;
	mlx_put_image_to_window(map->mlx, map->win, map->ptr.image[map->i], SCREEN_WIDTH / 2, SCREEN_HEIGHT - 250);
	map->i++;
}

int	ft_render_the_game(t_map *map)
{
	mlx_clear_window(map->mlx, map->win);
	put_map(map);
	put_minimap(map);
	put_weapon(map);
	return (0);
}

void	draw_minimap_line(t_map *map, double x, double y)
{
	double	dx;
	double	dy;
	double	fx;
	double	fy;
	int		line;

	dx = x - 100;
	dy = y - 100;
	fx = 100;
	fy = 100;
	if (fabs(dx) > fabs(dy))
		line = fabs(dx);
	else
		line = fabs(dy);
	dx = (double)dx / (double)line;
	dy = (double)dy / (double)line;
	int i = 0;
	while (i <= line)
	{
		my_mlx_M_PIxel_put(&map->img, fx, fy, RED);
		fx += dx;
		fy += dy;
		i++;
	}
}

void	calc_minimap_line(t_map *map)
{
	double	x;
	double	y;

	x = 100;
	y = 100;
	x += (cos(map->angle) * 20);
	y += (sin(map->angle) * 20);
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

int	is_wall(t_map *map, int lenx, int leny)
{
	int	x;
	int	y;

	x = floor(lenx / 16);
	y = floor(leny / 16);
	if (y < 0 || y >= (map->my)
		|| x < 0 || x >= (map->mx))
		return (0);
	if (map->map[y][x] == '1')
		return (1);
	if (map->map[y][x] == 'D')
		return (2);
	if (map->map[y][x] == 'O')
		return (3);
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
			if (is_wall(map, ((map->position_x) + x), ((map->position_y) + y)) == 2)
				my_mlx_M_PIxel_put(&map->img, x, y, BLUE);
			else if (is_wall(map, ((map->position_x) + x), ((map->position_y) + y)) == 3)
				my_mlx_M_PIxel_put(&map->img, x, y, GREEN);
			else if (is_wall(map, ((map->position_x) + x), ((map->position_y) + y)))
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
	if (map->map[(int)floor((y + 6) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y + 6) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor((y - 6) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y - 6) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x + 6) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x + 6) / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x - 6) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x - 6) / 32)] == 'D')
		return ;
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}

void	ft_calc_back(t_map *map)
{
	double x;
	double y;

	x = map->player_x - (cos(map->angle) * map->move_speed);
	y = map->player_y - (sin(map->angle) * map->move_speed);
	if (map->map[(int)floor((y + 6) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y + 6) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor((y - 6) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y - 6) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x + 6) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x + 6) / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x - 6) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x - 6) / 32)] == 'D')
		return ;
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}

void	ft_calc_right_angle(t_map *map)
{
	double x;
	double y;

	x = map->player_x + (cos(map->angle + (M_PI / 2)) * map->move_speed);
	y = map->player_y + (sin(map->angle + (M_PI / 2)) * map->move_speed);
	if (map->map[(int)floor((y + 6) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y + 6) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor((y - 6) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y - 6) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x + 6) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x + 6) / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x - 6) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x - 6) / 32)] == 'D')
		return ;
	map->player_x = x;
	map->player_y = y;
	map->drawzy = 1;
}

void	ft_calc_left_angle(t_map *map)
{
	double x;
	double y;

	x = map->player_x + (cos(map->angle - (M_PI / 2)) * map->move_speed);
	y = map->player_y + (sin(map->angle - (M_PI / 2)) * map->move_speed);
	if (map->map[(int)floor((y + 6) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y + 6) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor((y - 6) / 32)][(int)floor(x / 32)] == '1'
		|| map->map[(int)floor((y - 6) / 32)][(int)floor(x / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x + 6) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x + 6) / 32)] == 'D')
		return ;
	if (map->map[(int)floor(y / 32)][(int)floor((x - 6) / 32)] == '1'
		|| map->map[(int)floor(y / 32)][(int)floor((x - 6) / 32)] == 'D')
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

int ft_mouse_rotation(int x, int y, t_map *map)
{
	int		tmp;
	double	helper;
	
	tmp = map->mouse_x;
	helper = 0;
	if (map->focus_mode == 0)
	{
		if (x > SCREEN_WIDTH || x < 0 || y > SCREEN_HEIGHT || y < 0)
		{
			mlx_mouse_move(map->win, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
			map->mouse_x = (SCREEN_WIDTH / 2);
			map->mouse_y = (SCREEN_HEIGHT / 2);
			return 0;
		}
		if (x != map->mouse_x)
		{
			helper = x - map->mouse_x;
			map->angle += helper * 0.0007f;
			map->mouse_x = x;
			map->drawzy = 1;
		}
	}
	return 0;
}

int	execution(t_map map)
{
	map.img.img = mlx_new_image(map.mlx, map.width, map.height);
	mlx_hook(map.win, 17, 0, &close_window, &map);
	map.img.addr = mlx_get_data_addr(map.img.img,
			&map.img.bits_per_M_PIxel, &map.img.line_length,
			&map.img.endian);
	mlx_mouse_hide();
	mlx_mouse_move(map.win, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	mlx_mouse_get_pos(map.win, &map.mouse_x, &map.mouse_y);
	mlx_hook(map.win, 2, 0, key_hook1, &map);
	mlx_hook(map.win, 3, 0, key_hook2, &map);
	mlx_hook(map.win, 6, 0, ft_mouse_rotation, &map);
	mlx_loop_hook(map.mlx, ft_update, &map);
	mlx_loop(map.mlx);
	return (0);
}
