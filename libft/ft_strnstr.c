/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:41:16 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/19 00:26:14 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = 0;
	while (haystack[i] && i < len && needle[0])
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
	if ((needle[j] == '\0' && (i + j) <= len) || haystack == needle)
		return ((char *)haystack + i);
	else
		return (NULL);
}
