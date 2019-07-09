/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_init_priority.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:39:51 by nkellum           #+#    #+#             */
/*   Updated: 2019/04/26 17:38:18 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	prioritize(t_flags *flags)
{
	if (flags->positive_sign && flags->space)
		flags->space = 0;
	if (flags->positive_sign && flags->space)
		flags->space = 0;
	if (flags->precision_dot && flags->pad_zero
		&& flags->fmt_char != 'c' && flags->fmt_char != 's'
		&& flags->fmt_char != 'f')
		flags->pad_zero = 0;
	if (flags->pad_zero && flags->left_adjustment)
		flags->pad_zero = 0;
	if (flags->pad_zero && flags->left_adjustment)
		flags->pad_zero = 0;
	if (flags->fmt_char == 'u')
	{
		flags->space = 0;
		flags->positive_sign = 0;
	}
}

void	init_flags(t_flags *flags)
{
	flags->left_adjustment = 0;
	flags->is_neg = 0;
	flags->positive_sign = 0;
	flags->space = 0;
	flags->pad_zero = 0;
	flags->hash = 0;
	flags->precision_dot = 0;
	flags->precision_val = 0;
	flags->field_length = 0;
	flags->h = 0;
	flags->l = 0;
	flags->upper_l = 0;
	flags->str = "";
}

void	init_flag_struct(t_flags **flags)
{
	if ((*flags = malloc(sizeof(t_flags))) == NULL)
		return ;
	init_flags(*flags);
}
