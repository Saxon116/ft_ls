/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 14:26:00 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/09 16:00:11 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_precision(t_flags *flags, int str_length)
{
	int i;
	int length;

	length = str_length ? str_length : num_length(flags->i);
	i = 0;
	if (flags->is_neg)
	{
		ft_putchar_p('-', flags);
		flags->i = -flags->i;
	}
	else if (flags->positive_sign)
		ft_putchar_p('+', flags);
	while (i < flags->precision_val - length + flags->is_neg)
	{
		ft_putchar_p('0', flags);
		i++;
	}
	if (!str_length)
		print_ull_if_needed(flags);
}

void	print_field_sign_flag(t_flags *flags)
{
	if (flags->pad_zero && !flags->precision_dot && flags->is_neg)
	{
		ft_putchar_p('-', flags);
		flags->i = -flags->i;
	}
	if (flags->positive_sign && !flags->precision_dot && !flags->is_neg
	&& flags->pad_zero)
		ft_putchar_p('+', flags);
	if (flags->space && flags->field_length <= (num_length(flags->i))
	&& !flags->is_neg)
		ft_putchar_p(' ', flags);
	if (flags->i == 0 && flags->space)
	{
		ft_putchar_p(' ', flags);
		flags->field_length--;
	}
}

void	print_field(t_flags *flags, int str_length)
{
	int i;
	int length;

	i = 0;
	length = str_length ? str_length : num_length(flags->i);
	print_field_sign_flag(flags);
	while (i < flags->field_length - length
	- (flags->precision_val - length) * (flags->precision_val - length > 0)
	* flags->precision_dot - (flags->is_neg * flags->precision_dot
	* (flags->precision_val - length >= 0))
	- (flags->positive_sign * !flags->is_neg))
	{
		if (flags->pad_zero && !flags->precision_dot)
			ft_putchar_p('0', flags);
		else
			ft_putchar_p(' ', flags);
		i++;
	}
	if (flags->positive_sign && !flags->precision_dot && !flags->is_neg
	&& !flags->pad_zero && flags->fmt_char != 'o' && !flags->left_adjustment)
		ft_putchar_p('+', flags);
}

void	apply_conversion_flags(va_list ap, t_flags *flags)
{
	if (flags->l != 0)
	{
		flags->i = va_arg(ap, long long);
		if (flags->fmt_char == 'u')
			flags->i = (unsigned long long)flags->i;
	}
	else
	{
		flags->i = va_arg(ap, int);
		if (flags->fmt_char == 'u')
			flags->i = (unsigned int)flags->i;
	}
	if (flags->h != 0 && !flags->l)
	{
		flags->i = (short int)flags->i;
		if (flags->fmt_char == 'u')
			flags->i = (unsigned short int)flags->i;
		if (flags->h >= 2)
		{
			flags->i = (char)flags->i;
			if (flags->fmt_char == 'u')
				flags->i = (unsigned char)flags->i;
		}
	}
}
