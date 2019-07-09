/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:37:48 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/09 16:01:10 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_ull_if_needed(t_flags *flags)
{
	if (flags->i > 9223372036854775807 ||
	flags->i < -9223372036854775807)
	{
		if (flags->i < 0)
			ft_uputnbr(flags->i, flags, 1);
		else
			ft_uputnbr(flags->i, flags, 0);
	}
	else
	{
		if (flags->fmt_char == 'u')
			ft_uputnbr(flags->i, flags, 0);
		else
		{
			if (flags->positive_sign && !flags->is_neg
			&& flags->left_adjustment && !flags->precision_dot)
				ft_putchar_p('+', flags);
			ft_putnbr_p(flags->i, flags);
		}
	}
}

int		check_octal_format(va_list ap, t_flags *flags)
{
	int i;

	i = 0;
	if (flags->l == 1)
		flags->i = va_arg(ap, unsigned long);
	else if (flags->l >= 2)
		flags->i = va_arg(ap, unsigned long long);
	else
		flags->i = va_arg(ap, unsigned int);
	if (flags->precision_dot && !flags->precision_val
		&& flags->i == 0 && !flags->hash)
	{
		while (i < flags->field_length)
		{
			ft_putchar_p(' ', flags);
			i++;
		}
		return (0);
	}
	if (flags->i == 0 && flags->precision_dot && !flags->precision_val
	&& !flags->hash)
		return (0);
	return (1);
}

void	print_octal(va_list ap, t_flags *flags)
{
	if (!check_octal_format(ap, flags))
		return ;
	if (flags->h == 1)
		flags->i = (unsigned short int)flags->i;
	if (flags->h >= 2)
		flags->i = (unsigned char)flags->i;
	if (flags->hash && !flags->precision_dot)
		flags->field_length--;
	flags->str = ft_utoa_base(flags->i, 8, 0);
	if (!flags->left_adjustment)
		print_field(flags, ft_strlen_p(flags->str));
	if (flags->hash && !flags->precision_dot && flags->i)
		ft_putchar_p('0', flags);
	if (flags->precision_dot)
		print_precision(flags, ft_strlen_p(flags->str));
	ft_putstr_p(flags->str, flags);
	free(flags->str);
	if (flags->left_adjustment)
		print_field(flags, 0);
}
