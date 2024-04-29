/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfilecontant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:45:43 by mel-jira          #+#    #+#             */
/*   Updated: 2024/04/23 15:25:33 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_lines(int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		free(line);
	}
	close(fd);
	return (i);
}

char	**readfilecontant(char *mapname, int fd, int len, int i)
{
	char	*line;
	char	**map;

	line = NULL;
	map = (char **)malloc(sizeof(char *) * (len + 1));
	if (!map)
		return (NULL);
	fd = open(mapname, O_RDONLY);
	while (++i < len)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
		{
			map[i] = ft_substr(line, 0, (ft_strlen(line) - 1));
			free(line);
		}
		else
			map[i] = line;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}
