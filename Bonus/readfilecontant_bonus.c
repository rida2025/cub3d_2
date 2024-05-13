/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfilecontant_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:45:43 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/09 16:34:49 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	map = (char **)ft_malloc(sizeof(char *) * (len + 1));
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
