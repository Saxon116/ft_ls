/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:43:18 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/09 16:00:15 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_misc(va_list ap, t_flags *flags)
{
	if (flags->fmt_char == 'o')
		print_octal(ap, flags);
	if (flags->fmt_char == 'x' || flags->fmt_char == 'X'
	|| flags->fmt_char == 'p')
		print_hex(ap, flags);
	if (flags->fmt_char == 'f')
	{
		flags->precision_val =
		flags->precision_dot ? flags->precision_val : 6;
		print_double(ap, flags);
	}
}

void	print_num(va_list ap, t_flags *flags)
{
	if (flags->fmt_char == 'd' || flags->fmt_char == 'i'
	|| flags->fmt_char == 'u')
	{
		apply_conversion_flags(ap, flags);
		if (flags->i == 0 && flags->precision_dot
		&& flags->precision_val == 0)
		{
			while ((flags->i)++ < flags->field_length)
				ft_putchar_p(' ', flags);
			return ;
		}
		if (flags->i < 0)
			flags->is_neg = 1;
		if (!flags->left_adjustment)
			print_field(flags, 0);
		if (flags->precision_dot)
			print_precision(flags, 0);
		else
			print_ull_if_needed(flags);
		if (flags->left_adjustment)
			print_field(flags, 0);
	}
	else
		print_misc(ap, flags);
}
