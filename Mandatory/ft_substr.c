/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:22:06 by mel-jira          #+#    #+#             */
/*   Updated: 2024/05/09 11:08:38 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	char	*ft_cpystr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*str;

	i = 0;
	size = ft_strlen(s);
	if (len > size - start)
	{
		len = size - start;
		str = (char *)ft_malloc((size - start) * sizeof(char) + 1);
	}
	else
		str = (char *)ft_malloc(len * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) <= start)
	{
		str = (char *)ft_malloc(1);
		if (str == NULL)
			return (NULL);
		*str = '\0';
		return (str);
	}
	str = ft_cpystr(s, start, len);
	return (str);
}
