/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:05:28 by nkellum           #+#    #+#             */
/*   Updated: 2019/04/25 14:43:21 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

long long	ft_pow(long long nb, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

int			get_size(long long value, int base)
{
	int i;

	i = 1;
	while (ft_pow(base, i) - 1 < value)
	{
		if (ft_pow(base, i) - 1 > 0 && ft_pow(base, i + 1) - 1 == -1)
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}

char		*ft_itoa_base(long long value, int base, int lowercase)
{
	int		i;
	char	*nbr;
	int		neg;

	neg = 0;
	if (value < 0)
	{
		if (base == 10)
			neg = 1;
		value *= -1;
	}
	i = get_size(value, base);
	nbr = (char*)malloc(sizeof(nbr) * i);
	nbr[i + neg] = '\0';
	while (i-- > 0)
	{
		nbr[i + neg] = (value % base) + (value % base > 9 ? 'A' - 10 : '0');
		if (nbr[i + neg] >= 'A' && nbr[i + neg] <= 'F' && lowercase)
			nbr[i + neg] = nbr[i + neg] + 32;
		value = value / base;
	}
	if (neg)
		nbr[0] = '-';
	return (nbr);
}
