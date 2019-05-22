/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:26:12 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/19 12:27:59 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*i;

	if (n == 0)
		return (s);
	i = (unsigned char *)s;
	while (n--)
	{
		*i = (unsigned char)c;
		if (n)
			i++;
	}
	return (s);
}
