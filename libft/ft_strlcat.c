/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 18:53:24 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/27 12:10:17 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int i;
	unsigned int length;

	i = 0;
	length = ft_strlen(dst);
	if (size == 0)
		return (ft_strlen(src));
	if (size == 1)
		return (ft_strlen(src) + 1);
	if (length > size)
		return (ft_strlen(src) + size);
	while (src[i] && i + length < size - 1)
	{
		dst[length + i] = src[i];
		i++;
	}
	dst[length + i] = '\0';
	return (length + ft_strlen(src));
}
