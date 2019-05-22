/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:16:36 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/23 15:00:35 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	numlength(int n)
{
	int i;
	int neg;

	i = 0;
	neg = 0;
	if (n == 0 || n == -0)
		return (1);
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	if (neg)
		return (-i);
	else
		return (i);
}

static void	isnegative(int *length, int *isneg, int *n)
{
	if (numlength(*n) < 0)
	{
		*length = -*length;
		*length += 1;
		*isneg = 1;
		*n = -*n;
	}
}

char		*ft_itoa(int n)
{
	char	*numstr;
	int		isneg;
	int		length;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0 || n == -0)
		return (ft_strdup("0"));
	length = numlength(n);
	isnegative(&length, &isneg, &n);
	i = length - 1;
	if ((numstr = malloc(length + 1)) == NULL)
		return (0);
	numstr[length] = '\0';
	if (isneg)
		numstr[0] = '-';
	while (n > 0)
	{
		numstr[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (numstr);
}
