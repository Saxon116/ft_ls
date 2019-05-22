/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:44:36 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/28 15:57:51 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*strnew;

	i = 0;
	if (!s)
		return (0);
	if ((strnew = malloc(len + 1)) == NULL)
		return (0);
	while (s[i + start] && i < len)
	{
		strnew[i] = s[i + start];
		i++;
	}
	strnew[i] = '\0';
	return (strnew);
}
