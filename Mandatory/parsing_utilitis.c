/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilitis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:47 by mel-jira          #+#    #+#             */
/*   Updated: 2024/04/28 18:06:03 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*fill_it1(char **map, int x, int y)
{
	char	*new_map;
	int		i;

	i = 0;
	new_map = NULL;
	new_map = ft_malloc(sizeof(char) * (x + 1));
	if (!new_map)
		return (NULL);
	while (i < x)
	{
		if (i == 0 || i > ft_strlen(map[y]))
			new_map[i] = ' ';
		else
		{
			new_map[i] = map[y][i - 1];
		}
		i++;
	}
	new_map[i] = '\0';
	return (new_map);
}

char	*fill_it2(int x)
{
	char	*new_map;
	int		i;

	i = 0;
	new_map = NULL;
	new_map = ft_malloc(sizeof(char) * (x + 1));
	if (!new_map)
		return (NULL);
	while (i < x)
	{
		new_map[i] = ' ';
		i++;
	}
	new_map[i] = '\0';
	return (new_map);
}

int	get_biggest_x(char **map)
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
	return (biggest);
}

int	get_biggest_y(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

char	**make_it_bigger_square(char **map, int x, int y, int i)
{
	char	**cpy;

	cpy = NULL;
	x = get_biggest_x(map) + 2;
	y = get_biggest_y(map) + 2;
	cpy = ft_malloc(sizeof(char *) * (y + 1));
	if (!cpy)
		return (NULL);
	cpy[0] = fill_it2(x);
	if (!cpy[0])
		return (NULL);
	while (++i <= (y - 2))
	{
		cpy[i] = fill_it1(map, (x), (i - 1));
		if (!cpy[i])
			return (NULL);
	}
	cpy[i] = fill_it2(x);
	if (!cpy[i])
		return (NULL);
	cpy[++i] = NULL;
	return (cpy);
}
