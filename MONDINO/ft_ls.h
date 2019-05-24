/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondino <jmondino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:58:28 by jmondino          #+#    #+#             */
/*   Updated: 2019/05/23 17:21:28 by jmondino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include "libft/libft.h"
# define OP(x) x == 'a' || x == 'r' || x == 'l' || x == 'R' || x == 't'

typedef struct 	s_shit
{
	char		*option;
	int			ac;
	int			index;
	char		**av;
}				t_shit;

void	ft_pathless(DIR *pDir, struct dirent *pDirent, t_shit *pShit);
void	ft_manypaths(DIR *pDir, struct dirent *pDirent, t_shit *pShit);
void	ft_parse(DIR *pDir, struct dirent *pDirent, t_shit *pShit);
void	ft_afftab(char **tab);
void	ft_asciiorder(char **tab);
void	ft_revtab(char **tab);
char	**ft_creatab(t_list *lst, int i);
int		ft_parseoption(char *av);
int		checkoption(char *option, char c);

#endif
