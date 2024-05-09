/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_contant_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:47:20 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/09 16:33:56 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_map_contant(t_map *map, char **map_contant, int i)
{
	char	**cpy;
	t_point	limit;

	limit.x = 0;
	limit.y = 0;
	cpy = NULL;
	if (is_only_map(map_contant, i))
		return (1);
	cpy = get_only_map(map_contant, i);
	if (!cpy)
		return (1);
	cpy = make_it_bigger_square(cpy, 0, 0, 0);
	if (!cpy)
		return (1);
	limit.x = get_biggest_x2(cpy, map);
	limit.y = get_biggest_y2(cpy, map);
	map->map = create_cpy(cpy);
	if (check_characters(cpy))
		return (1);
	can_access(cpy, 0, 0, limit);
	only1player(cpy, map, 0, 0);
	can_fall(cpy, map->player_x, map->player_y, limit);
	return (0);
}
