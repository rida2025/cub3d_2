/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:27:43 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/09 11:08:23 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		s2_len;
	int		i;
	int		j;

	s2_len = ft_strlen(s2);
	i = 0;
	j = 0;
	str = (char *)ft_malloc((ft_strlen(s1) + s2_len + 1) * sizeof(char));
	if (!str)
		return (free(s1), s1 = NULL, NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	s1 = NULL;
	return (str);
}
