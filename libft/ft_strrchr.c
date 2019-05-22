/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 12:16:46 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/27 12:17:45 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	s += i;
	if (c == '\0')
		return ((char *)s);
	while (i > -1)
	{
		if (*s == c)
			return ((char *)s);
		s--;
		i--;
	}
	return (NULL);
}
