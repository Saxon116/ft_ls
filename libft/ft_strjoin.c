/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:01:48 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/21 16:12:59 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*strnew;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	if ((strnew = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)) == NULL)
		return (0);
	while (s1[i])
	{
		strnew[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		strnew[i + j] = s2[j];
		j++;
	}
	strnew[i + j] = '\0';
	return (strnew);
}
