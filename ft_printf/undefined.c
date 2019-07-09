/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undefined.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:19:10 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/09 16:00:17 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_dpercent_field(t_flags *flags)
{
	int i;

	i = 0;
	if (flags->left_adjustment)
		ft_putchar_p('%', flags);
	while (i < flags->field_length - 1)
	{
		if (flags->pad_zero)
			ft_putchar_p('0', flags);
		else
			ft_putchar_p(' ', flags);
		i++;
	}
	if (!flags->left_adjustment)
		ft_putchar_p('%', flags);
}

void	get_dpercent_field(const char *str, t_flags *flags)
{
	int i;

	i = 0;
	while (str[i] != '%')
	{
		if (str[i] == '0')
			flags->pad_zero = 1;
		if (str[i] == '.')
			flags->precision_dot = 1;
		if (str[i] == '-')
			flags->left_adjustment = 1;
		if (str[i] >= '1' && str[i] <= '9' && !flags->precision_dot)
		{
			flags->field_length = ft_atoi_p(str + i);
			break ;
		}
		i++;
	}
	if (flags->left_adjustment && flags->pad_zero)
		flags->pad_zero = 0;
	print_dpercent_field(flags);
}

void	print_invalid_fmt_field(t_flags *flags)
{
	int i;

	i = 0;
	if (!contains("hlLjtzq", flags->c) ||
	(contains("hlLjtzq", flags->c) && !flags->left_adjustment))
	{
		if (!contains("hlLjtzq", flags->c) && flags->left_adjustment)
			ft_putchar_p(flags->c, flags);
		while (i < flags->field_length - 1)
		{
			if (flags->pad_zero)
				ft_putchar_p('0', flags);
			else
				ft_putchar_p(' ', flags);
			i++;
		}
		if (!contains("hlLjtzq", flags->c) && !flags->left_adjustment)
			ft_putchar_p(flags->c, flags);
	}
}

int		get_invalid_fmt_field(const char *str, t_flags *flags)
{
	int i;

	i = 0;
	while (contains("-+#*01234564789. ", str[i]))
	{
		if (str[i] == '0')
			flags->pad_zero = 1;
		if (str[i] == '-')
			flags->left_adjustment = 1;
		if (str[i] == '.')
			flags->precision_dot = 1;
		if (str[i] >= '1' && str[i] <= '9' && !flags->precision_dot)
		{
			flags->field_length = ft_atoi_p(str + i);
			i += num_length(flags->field_length) - 1;
		}
		i++;
	}
	while (contains("hlLjtzq", str[i]))
		i++;
	flags->c = str[i];
	print_invalid_fmt_field(flags);
	return (i);
}
