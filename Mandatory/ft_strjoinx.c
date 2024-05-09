/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:26:59 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/09 11:08:26 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoinx(char *remain, char *buffer)
{
	char	*str;
	int		s2_len;
	int		i;
	int		j;

	s2_len = ft_strlen(buffer);
	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(remain) + s2_len + 1) * sizeof(char));
	if (!str)
		return (free(remain), remain = NULL, NULL);
	while (remain[i] != '\0')
	{
		str[i] = remain[i];
		i++;
	}
	while (buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[i] = '\0';
	free(remain);
	remain = NULL;
	return (str);
}
