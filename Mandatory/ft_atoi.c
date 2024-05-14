/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:39:56 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/14 16:51:39 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi(char *arg, int i)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (arg[i] == ' ' || (arg[i] >= 9 && arg[i] <= 13))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i] && arg[i] <= '9' && arg[i] >= '0')
	{
		if (((result * 10) + (arg[i] - '0')) * sign > 255 \
		|| ((result * 10) + (arg[i] - '0')) * sign < 0)
			return (-1);
		result = (result * 10) + (arg[i] - '0');
		i++;
	}
	if (arg[i])
		return (-1);
	return ((result * sign));
}
