/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:17:10 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/21 12:18:48 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		*(unsigned char*)dest = *(unsigned char*)src;
		dest++;
		if ((unsigned char)c == *(unsigned char*)src)
			break ;
		src++;
		i++;
	}
	if (i == n)
		return (NULL);
	return ((unsigned char*)dest);
}
