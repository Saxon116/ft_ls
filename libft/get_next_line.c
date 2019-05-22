/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:38:46 by nkellum           #+#    #+#             */
/*   Updated: 2019/01/09 15:14:34 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_realloc(char **dest, size_t size)
{
	if (dest || *dest)
		free(*dest);
	if ((*dest = malloc(size + 1)) == NULL)
		return ;
}

void	fill_temp(char **temp, char *buff, int keeptemp)
{
	char *oldtemp;

	if (*temp && keeptemp)
	{
		oldtemp = ft_strdup(*temp);
		ft_realloc(&*temp, ft_strlen(oldtemp) + ft_strlen(buff));
		ft_memcpy(*temp, oldtemp, ft_strlen(oldtemp));
		ft_strncpy(*temp + ft_strlen(oldtemp), buff, ft_strlen(buff));
		temp[0][ft_strlen(oldtemp) + ft_strlen(buff)] = '\0';
		free(oldtemp);
	}
	else
	{
		ft_realloc(&*temp, ft_strlen(buff));
		ft_memcpy(*temp, buff, ft_strlen(buff));
		temp[0][ft_strlen(buff)] = '\0';
	}
}

int		check_temp(char **temp, char **line, int stillreading)
{
	int		i;
	char	*temptemp;

	i = ft_strchr(*temp, '\n') - *temp;
	temptemp = ft_strdup(*temp);
	if (ft_strchr(*temp, '\n'))
	{
		ft_realloc(&*line, i);
		ft_memcpy(*line, *temp, i);
		line[0][i] = '\0';
		free(*temp);
		*temp = ft_strdup(temptemp + i + 1);
		free(temptemp);
		return (1);
	}
	free(temptemp);
	if (!stillreading && temp[0][0] != '\0')
	{
		ft_realloc(&*line, ft_strlen(*temp));
		ft_memcpy(*line, *temp, ft_strlen(*temp));
		line[0][ft_strlen(*temp)] = '\0';
		temp[0][0] = '\0';
		return (1);
	}
	return (0);
}

int		extend(char *buff, char **temp, char **line)
{
	int i;

	i = 0;
	if (ft_strchr(buff, '\n'))
	{
		i = ft_strchr(buff, '\n') - buff;
		if (*temp)
		{
			ft_realloc(&*line, ft_strlen(*temp) + i);
			ft_memcpy(*line, *temp, ft_strlen(*temp));
			ft_strncpy(*line + ft_strlen(*temp), buff, i);
			line[0][ft_strlen(*temp) + i] = '\0';
			fill_temp(&*temp, buff + i + 1, 0);
		}
		else
		{
			ft_realloc(&*line, i);
			ft_memcpy(*line, buff, i);
			line[0][i] = '\0';
			fill_temp(&*temp, buff + i + 1, 0);
		}
	}
	else
		fill_temp(&*temp, buff, 1);
	return (buff[0] == '\n' ? 1 : i);
}

int		get_next_line(const int fd, char **line)
{
	static char	*temp;
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0))
		return (-1);
	*line = NULL;
	if (temp && check_temp(&temp, &*line, 1))
		return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (extend(buf, &temp, &*line))
			break ;
	}
	if (!ret)
	{
		if (temp != NULL && check_temp(&temp, &*line, 0))
			return (1);
		return (0);
	}
	return (1);
}
