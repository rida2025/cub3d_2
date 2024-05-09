/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utlitis2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:06:43 by mel-jira          #+#    #+#             */
/*   Updated: 2024/04/28 18:23:38 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_biggest_x2(char **map, t_map *info)
{
	int	x;
	int	y;
	int	biggest;

	x = 0;
	y = 0;
	biggest = 0;
	while (map[y])
	{
		while (map[y] && map[y][x])
			x++;
		if (x > biggest)
			biggest = x;
		x = 0;
		y++;
	}
	info->mx = biggest;
	return (biggest);
}

int	get_biggest_y2(char **map, t_map *info)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	info->my = y;
	return (y);
}

void	can_access(char **map, int x, int y, t_point limit)
{
	if (x < 0 || y < 0 || x >= limit.x || y >= limit.y
		|| (map[y][x] && (map[y][x] == '1' || map[y][x] == '-' )))
		return ;
	if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		write(2, "Error in map scation\n", 21);
		exit(3);
	}
	map[y][x] = '-';
	can_access(map, x + 1, y, limit);
	can_access(map, x - 1, y, limit);
	can_access(map, x, y + 1, limit);
	can_access(map, x, y - 1, limit);
}

void	can_fall(char **map, int x, int y, t_point limit)
{
	if (x < 0 || y < 0 || x >= limit.x || y >= limit.y
		|| (map[y][x] && (map[y][x] == '1' || map[y][x] == '-' )))
		return ;
	if (map[y][x] == ' ')
	{
		write(2, "Error in map scation the player is falling\n", 44);
		exit(3);
	}
	map[y][x] = '-';
	can_fall(map, x + 1, y, limit);
	can_fall(map, x - 1, y, limit);
	can_fall(map, x, y + 1, limit);
	can_fall(map, x, y - 1, limit);
}

int	search_line(char *str, char *look)
{
	int	i;
	int	ok;

	i = 0;
	ok = 0;
	while (str[i])
	{
		if (ft_strchr(look, str[i]))
			ok++;
		i++;
	}
	return (ok);
}
