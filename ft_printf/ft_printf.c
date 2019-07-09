/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:58:03 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/09 16:00:20 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	check_format(const char *fmt)
{
	int		i;
	char	*formats;
	char	*flags;

	i = 0;
	formats = "cspdiouxXf%";
	flags = " .#0123456789-+hlL";
	while (fmt[i])
	{
		if (contains(formats, fmt[i]))
			return (fmt[i]);
		if (!contains(flags, fmt[i]))
			return ('$');
		i++;
	}
	if (contains("hlLjtzq", fmt[i - 1]))
		return ('$');
	return ('\0');
}

void	analyse_format(va_list ap, const char *fmt, char c, t_flags *flags)
{
	int		i;
	char	*str_formats;

	init_flags(flags);
	flags->fmt_str = ft_strsub(fmt, 0, ft_strchr(fmt, c) - fmt);
	flags->fmt_char = c;
	flags->h = contains(flags->fmt_str, 'h');
	flags->l = contains(flags->fmt_str, 'l');
	flags->upper_l = contains(flags->fmt_str, 'L');
	get_flags(flags);
	i = 0;
	str_formats = "cs";
	if (contains(str_formats, c))
	{
		flags->is_str = 1;
		print_string(ap, flags);
	}
	else
	{
		flags->is_str = 0;
		print_num(ap, flags);
	}
	free(flags->fmt_str);
}

int		parse_format(va_list ap, char c, const char *fmt, t_flags *flags)
{
	if (c == '%')
	{
		get_dpercent_field(fmt, flags);
		return (ft_strchr(fmt, c) - fmt);
	}
	else if (c == '$')
		return (get_invalid_fmt_field(fmt, flags));
	else if (c != '\0')
	{
		analyse_format(ap, fmt, c, flags);
		return (ft_strchr(fmt, c) - fmt);
	}
	else
	{
		if (*fmt == ' ')
		{
			while (*(fmt + 1) == ' ')
				flags->space++;
		}
		else
			ft_putchar_p(*fmt, flags);
	}
	return (flags->space);
}

int		ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		chars_printed;
	char	c;
	t_flags	*flags;

	init_flag_struct(&flags);
	flags->chars_printed = 0;
	va_start(ap, fmt);
	while (*fmt && !(ft_strlen_p(fmt) == 1 && fmt[0] == '%'))
	{
		if (*fmt == '%')
		{
			fmt++;
			c = check_format(fmt);
			fmt += parse_format(ap, c, fmt, flags);
			flags->space = 0;
		}
		else
			ft_putchar_p(*fmt, flags);
		fmt++;
	}
	chars_printed = flags->chars_printed;
	free(flags);
	va_end(ap);
	return (chars_printed);
}
