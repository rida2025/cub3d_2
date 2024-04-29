/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:20:16 by mel-jira          #+#    #+#             */
/*   Updated: 2024/04/28 17:14:04 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error1(void)
{
	write(2, "Error permission denied can open map or it doesn't exist\n", 58);
}

void	error2(void)
{
	write(2, "Error in map\n", 12);
}

void	error43(void)
{
	write(2, "Error in collores and in texture\n", 34);
}

void	error5(void)
{
	write(2, "Error in map name\n", 19);
}

void	error_player(void)
{
	write(2, "Error there is more then one player\n", 37);
}
