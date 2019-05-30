/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:05:38 by jmondino          #+#    #+#             */
/*   Updated: 2018/11/21 21:53:56 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	int				j;

	if (*needle == '\0')
		return (char *)haystack;
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
			{
				if ((i + ft_strlen(needle)) > len)
					return (NULL);
				return ((char *)haystack + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
