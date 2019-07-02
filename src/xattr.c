/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xattr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:36:42 by jmondino          #+#    #+#             */
/*   Updated: 2019/07/02 13:38:34 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int     get_xattr_num(char *attributes, int size)
{
    int         i;
    int         num;
    int         reset;

    reset = 0;
    num = 0;
    i = 0;
    while (i < size)
    {
        if (attributes[i] == '\0')
            num++;
        i++;
    }
    return (num);
}

char        **get_xattr_list(char *attributes, int size)
{
    char        **array;
    int         i;
    int         j;
    int         num_of_xattr;

    i = 0;
    j = 0;
    num_of_xattr = get_xattr_num(attributes, size);
    if ((array = malloc((num_of_xattr + 1) * sizeof(char*))) == NULL)
        return (0);
    while (i < num_of_xattr)
    {
        array[i] = ft_strdup(attributes + j);
        while ((attributes[j]) != '\0')
            j++;
        j++;
		i++;
    }
    array[i] = NULL;
    return (array);
}

int         *get_xattr_sizes(char **attributes, char *path, int length)
{
    int         *sizes;
    int         i;

    i = 0;
    if ((sizes = malloc(sizeof(int) * length)) == NULL)
        return (0);
    while (i < length)
    {
        sizes[i] = getxattr(path, attributes[i], NULL, 0, 0, XATTR_NOFOLLOW);
        i++;
    }
    return (sizes);

}
