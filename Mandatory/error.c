/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:20:16 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/09 12:10:57 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error1(void)
{
	write(2, "Error permission denied cant open map or it doesnt exist\n", 58);
}

void	error2(void)
{
	write(2, "Error in map saction\n", 22);
}

void	error43(void)
{
	write(2, "Error in collores or in texture saction of map\n", 48);
}

void	error5(void)
{
	write(2, "Error in map name\n", 19);
}

void	error_player(void)
{
	write(2, "Error there is more then one player\n", 37);
}
