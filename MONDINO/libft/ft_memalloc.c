/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:00:22 by jmondino          #+#    #+#             */
/*   Updated: 2018/11/30 21:30:49 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*str;

	if (size > 65535)
		return (NULL);
	if (!(str = (unsigned char *)malloc(sizeof(str) * (size + 1))))
		return (NULL);
	ft_bzero(str, size);
	return (str);
}
