/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:35:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/09 16:33:54 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_precision_str(t_flags *flags)
{
	int i;

	i = 0;
	while (i < flags->precision_val && flags->str && flags->str[i])
	{
		ft_putchar_p(flags->str[i], flags);
		i++;
	}
}

void	print_string_field(t_flags *flags)
{
	int i;

	i = 0;
	while (i < flags->field_length - (flags->fmt_char == 'c')
	- (ft_strlen_p(flags->str) *
	(flags->precision_val >= ft_strlen_p(flags->str)
	|| (!flags->precision_val && !flags->precision_dot)))
	- (flags->precision_val * (flags->precision_val < ft_strlen_p(flags->str))
	* (ft_strlen_p(flags->str) != 0)))
	{
		if (flags->pad_zero)
			ft_putchar_p('0', flags);
		else
			ft_putchar_p(' ', flags);
		i++;
	}
}

void	print_string(va_list ap, t_flags *flags)
{
	if (flags->fmt_char == 's')
		flags->str = va_arg(ap, char *);
	if (flags->str == NULL)
		flags->str = "(null)";
	if (flags->fmt_char == 'c')
		flags->c = va_arg(ap, int);
	if (!flags->left_adjustment)
		print_string_field(flags);
	if (flags->fmt_char == 's')
	{
		if (flags->precision_val > 0)
			print_precision_str(flags);
		else
		{
			if (!flags->precision_dot)
				ft_putstr_p(flags->str, flags);
		}
	}
	if (flags->fmt_char == 'c')
		ft_putchar_p(flags->c, flags);
	if (flags->left_adjustment)
		print_string_field(flags);
}
