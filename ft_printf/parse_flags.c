/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:21:44 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/09 16:33:30 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_pad_zero(t_flags *flags)
{
	int i;

	i = 0;
	while (flags->fmt_str[i])
	{
		if (ft_isdigit(flags->fmt_str[i]))
		{
			if (flags->fmt_str[i] == '0')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int		return_num_in_fmt(t_flags *flags, int startindex, int endindex)
{
	int		num;
	char	*str;

	str = ft_strsub(flags->fmt_str, startindex, endindex - startindex);
	num = ft_atoi_p(str);
	free(str);
	return (num);
}

int		get_num_in_fmt(t_flags *flags, int skipindex)
{
	int i;
	int startindex;
	int endindex;

	i = skipindex;
	startindex = -1;
	endindex = -1;
	while (flags->fmt_str[i])
	{
		if (ft_isdigit(flags->fmt_str[i]) && startindex == -1)
			startindex = i;
		if (!ft_isdigit(flags->fmt_str[i]) && startindex != -1)
		{
			endindex = i;
			break ;
		}
		if (!flags->fmt_str[i + 1] && startindex != -1)
			endindex = i + 1;
		i++;
	}
	if (startindex != -1 && endindex != -1)
		return (return_num_in_fmt(flags, startindex, endindex));
	return (0);
}

int		num_before_precision(t_flags *flags)
{
	int i;

	i = 0;
	if (contains(flags->fmt_str, '.'))
	{
		while (flags->fmt_str[i] && flags->fmt_str[i] != '.')
		{
			if (ft_isdigit(flags->fmt_str[i])
			&& flags->fmt_str[i] != '0')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

void	get_flags(t_flags *flags)
{
	if (contains(flags->fmt_str, '.'))
		flags->precision_dot = 1;
	if (contains(flags->fmt_str, '-'))
		flags->left_adjustment = 1;
	if (contains(flags->fmt_str, '+'))
		flags->positive_sign = 1;
	if (contains(flags->fmt_str, ' '))
		flags->space = 1;
	if (contains(flags->fmt_str, '#'))
		flags->hash = 1;
	flags->pad_zero = get_pad_zero(flags);
	if (flags->pad_zero)
	{
		if (num_before_precision(flags))
			flags->field_length = get_num_in_fmt(flags,
			(ft_strchr(flags->fmt_str, '0')
			- flags->fmt_str) + 1);
	}
	else if (num_before_precision(flags))
		flags->field_length = get_num_in_fmt(flags, 0);
	if (flags->precision_dot)
		flags->precision_val = get_num_in_fmt(flags,
		(ft_strchr(flags->fmt_str, '.') - flags->fmt_str) + 1);
	prioritize(flags);
}
