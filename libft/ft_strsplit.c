/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:17:27 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/26 13:12:45 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		num_of_words(char *s, char c)
{
	int words;
	int i;
	int isword;

	i = 0;
	isword = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
			isword = 0;
		else if (!isword)
		{
			words++;
			isword = 1;
		}
		i++;
	}
	return (words);
}

static int		wordindex(char *s, char c, int n)
{
	int words;
	int i;
	int isword;

	i = 0;
	isword = 0;
	words = -1;
	while (s[i])
	{
		if (s[i] == c)
			isword = 0;
		else if (!isword)
		{
			words++;
			isword = 1;
		}
		if (words == n)
			return (i);
		i++;
	}
	return (-1);
}

static int		wordlen(char *s, char c, int n)
{
	int i;
	int length;

	length = 0;
	i = wordindex(s, c, n);
	while (s[i + length] != c && s[i + length])
		length++;
	return (length);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s || (array = malloc(sizeof(char *) *
	num_of_words((char *)s, c) + 1)) == NULL)
		return (0);
	while (i < num_of_words((char *)s, c))
	{
		if ((array[i] = malloc(sizeof(char) *
		wordlen((char *)s, c, i) + 1)) == NULL)
			return (0);
		j = 0;
		while (j < wordlen((char *)s, c, i))
		{
			array[i][j] = s[wordindex((char *)s, c, i) + j];
			j++;
		}
		array[i][j] = '\0';
		i++;
	}
	array[i] = 0;
	return (array);
}
