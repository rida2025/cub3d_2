/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:25:13 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/09 16:33:58 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_it(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 3;
	while (str[i])
		i++;
	if (i > 0)
		i--;
	else
		return (1);
	while (str[i] && i >= size && size > 0)
	{
		i--;
		size--;
	}
	if (ft_strcmp(&str[i], ".cub") != 0)
		return (1);
	return (0);
}

int	check_name(char *str)
{
	return (check_it(str));
}
