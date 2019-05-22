/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 12:25:41 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/18 23:45:32 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (haystack[i] && needle[0])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (needle[j])
			{
				if (haystack[i + j] != needle[j])
					break ;
				j++;
			}
			if (needle[j] == '\0')
				break ;
		}
		i++;
	}
	if (needle[j] == '\0')
		return ((char *)haystack + i);
	else
		return (NULL);
}
