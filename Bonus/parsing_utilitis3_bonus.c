/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilitis3_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:08:00 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/10 13:31:53 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_only_map(char **map, int i)
{
	int	x;

	x = 0;
	while (map[(i)])
	{
		if (!search_line(map[(i)], "01NSWE"))
			return (1);
		(i)++;
	}
	return (0);
}

int	map_size(char **map, int i)
{
	int	value;

	value = 0;
	while (map[i])
	{
		i++;
		value++;
	}
	return (value);
}

char	**get_only_map(char **map, int i)
{
	char	**new_map;
	int		p;
	int		y;

	new_map = NULL;
	p = 0;
	y = map_size(map, i);
	new_map = malloc(sizeof(char *) * (y + 1));
	if (!new_map)
		return (NULL);
	while (map[(i + p)])
	{
		new_map[p] = ft_strdup(map[(i + p)]);
		p++;
	}
	new_map[p] = NULL;
	return (new_map);
}

void	only1player(char **map, t_map *info, int y, int x)
{
	int		player;
	char	i;

	player = 0;
	i = 'A';
	while (map[y])
	{
		while (map[y] && map[y][x])
		{
			i = map[y][x];
			if (i == 'N' || i == 'S' || i == 'W' || i == 'E')
			{
				player++;
				info->player_x = x;
				info->player_y = y;
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (player != 1)
		return (error_player(), exit(1));
}

int	check_characters(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y] && map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'N'
				&& map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != 'W'
				&& map[y][x] != ' ' && map[y][x] != 'D' && map[y][x] != 'O')
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
