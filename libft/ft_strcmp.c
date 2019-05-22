/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:46:30 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/30 12:56:12 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1)
	{
		if (*s1 > *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s1 < *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	if (*s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	else
		return (0);
}
