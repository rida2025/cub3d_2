/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_map_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:23:59 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/09 16:34:03 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	**create_cpy(char **map)
{
	char	**cpymap;
	int		i;
	int		x;

	x = 0;
	i = -1;
	while (map[x])
		x++;
	cpymap = (char **)ft_malloc(sizeof(char *) * (x + 1));
	if (!cpymap)
		return (NULL);
	while (map[++i])
	{
		cpymap[i] = ft_strdup(map[i]);
	}
	cpymap[i] = NULL;
	return (cpymap);
}
