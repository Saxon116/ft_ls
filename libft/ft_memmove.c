/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:30:07 by jmondino          #+#    #+#             */
/*   Updated: 2018/11/30 21:16:01 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dest;
	char	*sorc;

	dest = (char *)dst;
	sorc = (char *)src;
	if ((char *)src == (char *)dst)
		return (dst);
	if ((char *)src < (char *)dst)
	{
		i = len - 1;
		while (len > 0)
		{
			dest[i] = sorc[i];
			len--;
			i--;
		}
		return (dest);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
