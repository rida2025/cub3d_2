/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:00:27 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/08 16:35:32 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 2)
	{
		if (parsing(&map, argv[1]))
			return (1);
		if (execution(map))
			return (1);
	}
	return (0);
}