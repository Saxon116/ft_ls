/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 10:40:08 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/09 16:01:30 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putnbr_p(long long n, t_flags *flags)
{
	if (n < 0)
	{
		ft_putchar_p('-', flags);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_p(n / 10, flags);
	ft_putchar_p((n % 10) + '0', flags);
}
