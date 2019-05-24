/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:14:31 by jmondino          #+#    #+#             */
/*   Updated: 2018/12/05 15:39:11 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nospaces(char const *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		count++;
		i++;
	}
	while (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t')
	{
		count--;
		i--;
	}
	return (count);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s)
	{
		if (!(str = (char *)malloc(sizeof(char) * ft_nospaces(s) + 1)))
			return (NULL);
		i = 0;
		j = 0;
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			i++;
		while (s[i])
			str[j++] = s[i++];
		while (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t')
		{
			str[j] = '\0';
			j--;
			i--;
		}
		str[j] = '\0';
		return (str);
	}
	return (NULL);
}
