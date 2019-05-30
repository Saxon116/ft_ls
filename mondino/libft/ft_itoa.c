/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 23:23:26 by jmondino          #+#    #+#             */
/*   Updated: 2018/11/30 21:33:12 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		size(int n)
{
	int		count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n /= 10)
		count++;
	return (count + 1);
}

static char		*rev(char *str)
{
	int		i;
	int		j;
	char	stock;

	i = 0;
	j = 0;
	if (*str == '-')
		str++;
	while (str[i])
		i++;
	i--;
	while (j < i)
	{
		stock = str[i];
		str[i] = str[j];
		str[j] = stock;
		i--;
		j++;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		temp;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(s = (char *)malloc(sizeof(char) * (size(n)) + 1)))
		return (NULL);
	i = 0;
	temp = size(n);
	if (n < 0)
	{
		s[i] = '-';
		n = -n;
		i++;
	}
	while (i < temp)
	{
		s[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	s[i] = '\0';
	rev(s);
	return (s);
}
