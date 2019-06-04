/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:27:45 by jmondino          #+#    #+#             */
/*   Updated: 2018/12/01 10:38:04 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlst;
	t_list	*temp;

	if (lst)
	{
		if (!(newlst = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		temp = f(lst);
		newlst = temp;
		while (lst->next)
		{
			lst = lst->next;
			temp->next = f(lst);
			temp = temp->next;
		}
		return (newlst);
	}
	return (NULL);
}
