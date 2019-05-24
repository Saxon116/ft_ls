/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 19:02:50 by jmondino          #+#    #+#             */
/*   Updated: 2019/01/24 16:58:33 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_checkstock(char *buff, char **line, char **stock)
{
	char	*tmp;

	*line = ft_strfchr(*stock, '\n');
	tmp = (buff == NULL) ? ft_strdup(ft_strchr(*stock, '\n') + 1) :
		ft_strjoin(ft_strchr(*stock, '\n') + 1, buff);
	ft_memdel((void **)stock);
	*stock = tmp;
	return (0);
}

static int		ft_checkbuff(char *buff, char **line, char **stock)
{
	char	*tmp;

	tmp = ft_strfchr(buff, '\n');
	*line = (*stock == NULL) ? ft_strdup(tmp) :
		ft_strjoin(*stock, tmp);
	ft_memdel((void **)&tmp);
	tmp = (*stock == NULL) ? ft_strjoin(*stock, ft_strchr(buff, '\n') + 1) :
		ft_strdup(ft_strchr(buff, '\n') + 1);
	ft_memdel((void **)stock);
	*stock = tmp;
	return (0);
}

static int		ft_cutstr(char *buff, char **line, char **stock)
{
	char	*tmp;

	if (*stock == NULL)
		*stock = ft_strdup("");
	if (ft_iscinstr(*stock, '\n'))
		return (ft_checkstock(buff, line, stock));
	if (ft_iscinstr(buff, '\n'))
		return (ft_checkbuff(buff, line, stock));
	tmp = ft_strjoin(*stock, buff);
	ft_memdel((void **)stock);
	*stock = tmp;
	return (1);
}

static void		ft_afterread(char **line, char **stock)
{
	char	*tmp;

	tmp = ft_strfchr(*stock, '\n');
	*line = (ft_iscinstr(*stock, '\n')) ? ft_strdup(tmp) :
		ft_strdup(*stock);
	ft_memdel((void **)&tmp);
	tmp = (ft_iscinstr(*stock, '\n')) ? ft_strdup(ft_strchr(*stock, '\n') + 1) :
		NULL;
	ft_memdel((void **)stock);
	*stock = tmp;
}

int				get_next_line(const int fd, char **line)
{
	static char		*stock;
	char			buff[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || read(fd, buff, 0) == -1)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (ft_cutstr(buff, line, &stock) == 0)
			return (1);
		ft_bzero(buff, BUFF_SIZE);
	}
	if (stock && *stock != '\0')
	{
		ft_afterread(line, &stock);
		return (1);
	}
	return (0);
}
