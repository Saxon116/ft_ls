/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:13:55 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/27 12:39:05 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int start;
	int end;
	int length;

	if (!s)
		return (0);
	length = ft_strlen(s);
	start = 0;
	end = length - 1;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	if (start == 0 && end == (length - 1))
		return (ft_strdup((char *)s));
	if (start > end)
		return (ft_strdup("\0"));
	if (ft_strsub(s, start, end - start + 1))
		return (ft_strsub(s, start, end - start + 1));
	return (NULL);
}
