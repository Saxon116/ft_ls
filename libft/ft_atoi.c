/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:59:06 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/30 13:03:56 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int num;
	int isneg;
	int i;

	i = 0;
	isneg = 0;
	num = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		isneg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		num *= 10;
		num += ((int)str[i] - 48);
		i++;
	}
	if (isneg)
		return (-num);
	else
		return (num);
}
