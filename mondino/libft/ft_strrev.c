/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:18:56 by jmondino          #+#    #+#             */
/*   Updated: 2018/12/03 14:28:56 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		n;
	char	stock;

	n = 0;
	i = 0;
	while (str[i])
		i++;
	i--;
	while (n < i)
	{
		stock = str[i];
		str[i] = str[n];
		str[n] = stock;
		i--;
		n++;
	}
	return (str);
}
