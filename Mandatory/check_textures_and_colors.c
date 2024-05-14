/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_and_colors.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:46:40 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/14 19:11:04 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_colors(t_map *map, char *line, t_mapheader *mapheader, int i)
{
	int	f_or_c;

	if (!ft_strncmp(&line[i], "F", 1))
	{
		mapheader->f += 1;
		f_or_c = 0;
	}
	else if (!ft_strncmp(&line[i], "C", 1))
	{
		mapheader->c += 1;
		f_or_c = 1;
	}
	else
		return (1);
	i += 1;
	if (!line[i])
		return (1);
	while (line[i] && ft_is_space(line[i]))
		(i)++;
	if (valid_colors(map, &line[i], f_or_c))
		return (1);
	return (0);
}

int	path_exist(t_map *map, char *str, int direction)
{
	int	fd;

	fd = 0;
	if (!str)
		return (1);
	if (ft_strlen(str) == 0)
		return (1);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	if (direction == 1)
		map->north_path = str;
	else if (direction == 2)
		map->south_path = str;
	else if (direction == -1)
		map->west_path = str;
	else if (direction == 0)
		map->east_path = str;
	return (0);
}

int	check_texture(t_map *map, char *line, t_mapheader *mapheader, int i)
{
	int	direction;

	direction = 0;
	if (!ft_strncmp(&line[i], "NO", 2) && (++direction))
		mapheader->no += 1;
	else if (!ft_strncmp(&line[i], "SO", 2) && (++direction) && (++direction))
		mapheader->so += 1;
	else if (!ft_strncmp(&line[i], "WE", 2) && (--direction))
		mapheader->we += 1;
	else if (!ft_strncmp(&line[i], "EA", 2))
		mapheader->ea += 1;
	else
		return (1);
	i += 1;
	if (!line[i])
		return (1);
	i += 1;
	if (!line[i])
		return (1);
	while (line[i] && ft_is_space(line[i]))
		(i)++;
	if (!line[i] || path_exist(map, &line[i], direction))
		return (1);
	return (0);
}

int	check_line(t_map *map, char *line, t_mapheader *mapheader, int i)
{
	int	i2;

	i2 = 0;
	while (line[i] && ft_is_space(line[i]))
		i++;
	i2 = i;
	if (line[i])
	{
		if (check_texture(map, &line[i], mapheader, 0)
			&& check_colors(map, &line[i2], mapheader, 0))
			return (1);
	}
	return (0);
}

int	check_texture_and_colors(t_map *map, char **map_contant, int *i)
{
	t_mapheader	mapheader;

	basic_init(&mapheader);
	while (map_contant[*i] && stop_here2(map_contant[*i]))
	{
		if (check_line(map, map_contant[*i], &mapheader, 0))
			return (1);
		(*i)++;
	}
	if (mapheader.no != 1 || mapheader.ea != 1 || mapheader.we != 1
		|| mapheader.so != 1 || mapheader.f != 1 || mapheader.c != 1)
		return (1);
	return (0);
}
