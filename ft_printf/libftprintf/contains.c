/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:23:53 by nkellum           #+#    #+#             */
/*   Updated: 2019/04/25 14:33:01 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	contains(char *str, char c)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] == c)
			num++;
		i++;
	}
	return (num);
}
