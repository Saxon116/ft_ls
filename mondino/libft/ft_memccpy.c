/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:04:26 by jmondino          #+#    #+#             */
/*   Updated: 2018/11/30 21:32:55 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*sorc;
	unsigned char	*dest;
	size_t			i;

	sorc = (unsigned char *)src;
	dest = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		dest[i] = sorc[i];
		if (sorc[i] == (unsigned char)c)
			return ((dest + i + 1));
		i++;
	}
	return (NULL);
}
