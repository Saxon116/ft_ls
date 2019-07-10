/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:52:58 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/09 15:51:34 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include "libftprintf/libftprintf.h"

typedef	struct	s_flags
{
	char		*fmt_str;
	char		fmt_char;
	int			chars_printed;
	int			is_str;
	int			is_neg;
	int			left_adjustment;
	int			positive_sign;
	int			space;
	int			pad_zero;
	int			hash;
	int			precision_dot;
	int			precision_val;
	int			field_length;
	int			h;
	int			l;
	int			upper_l;
	long long	i;
	double		d;
	float		f;
	char		*str;
	char		c;
}				t_flags;

void			ft_putchar_p(char c, t_flags *flags);
void			ft_putstr_p(char const *s, t_flags *flags);
void			ft_putnbr_p(long long n, t_flags *flags);
void			ft_uputnbr(unsigned long long n, t_flags *flags, int isneg);
void			get_flags(t_flags *flags);
void			print_num(va_list ap, t_flags *flags);
void			print_hex(va_list ap, t_flags *flags);
void			print_string(va_list ap, t_flags *flags);
void			prioritize(t_flags *flags);
void			print_double(va_list ap, t_flags *flags);
int				ft_printf(const char *fmt, ...);
int				num_length(long long num);
void			init_flags(t_flags *flags);
void			print_dpercent_field(t_flags *flags);
void			get_dpercent_field(const char *str, t_flags *flags);
void			print_invalid_fmt_field(t_flags *flags);
int				get_invalid_fmt_field(const char *str, t_flags *flags);
void			init_flag_struct(t_flags **flags);
void			print_string(va_list ap, t_flags *flags);
void			print_octal(va_list ap, t_flags *flags);
void			print_precision(t_flags *flags, int str_length);
void			print_field(t_flags *flags, int str_length);
void			print_ull_if_needed(t_flags *flags);
void			apply_conversion_flags(va_list ap, t_flags *flags);

#endif
