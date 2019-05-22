/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:49:32 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/26 14:22:37 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int operation;
	int start;
	int end;

	if (dest == src)
		return (dest);
	if (dest > src)
	{
		start = n - 1;
		end = -1;
		operation = -1;
	}
	if (dest < src)
	{
		start = 0;
		end = n;
		operation = 1;
	}
	while (start != end)
	{
		*(((unsigned char*)dest) + start) = *(((unsigned char*)src) + start);
		start += operation;
	}
	return (dest);
}
