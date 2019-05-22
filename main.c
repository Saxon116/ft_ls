/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/05/21 20:39:10 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "libft/libft.h"

void list_dir(DIR *pDir)
{
	struct dirent *pDirent;

	while ((pDirent = readdir(pDir)) != NULL)
	{
		if(pDirent->d_name[0] != '.')
			printf("%s ", pDirent->d_name);
	}
	printf("\n");
	closedir(pDir);
}

int list_dir_recursive(char *dirname)
{
	struct dirent *pDirent;
	DIR *pDir;
	char path[ft_strlen(dirname) + 255]; // 255 more chars for subdirectory name

	pDir = opendir(dirname);
	if (pDir == NULL)
	{
	    	printf("Cannot open %s directory: %s\n", dirname, strerror(errno));
	    	return 1;
	}
	printf("%s:\n", dirname);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		if(pDirent->d_name[0] != '.') // ignore hidden entries
			printf("%s ", pDirent->d_name); // list entries normally
	}
	printf("\n");
	pDir = opendir(dirname); // resetting pDir to first file entry for new loop
	ft_strcpy(path, dirname); // set path to the current directory path
	while ((pDirent = readdir(pDir)) != NULL)
	{
		if(pDirent->d_name[0] != '.')
		{
			if(pDirent->d_type == DT_DIR) // if entry is a directory
			{
				printf("\n");
				if(dirname[ft_strlen(dirname) - 1] != '/')
					ft_strcat(path, "/");
				ft_strcat(path, pDirent->d_name); // add subdirectory name to full path
				list_dir_recursive(path); // list contents of subdirectory
				ft_bzero(path + ft_strlen(dirname),
				ft_strlen(pDirent->d_name) +
				dirname[ft_strlen(dirname) - 1] != '/'); // reset path for next subdirectory
			}
		}
	}
	closedir(pDir);
}


int main (int argc, char **argv)
{
	DIR *pDir;

	if(argc < 2)
		pDir = opendir("."); // if no directory specified, list this directory
	else
		pDir = opendir(argv[1]);
	if (pDir == NULL) {
	    printf("Cannot open directory: %s\n", strerror(errno));
	    return 1;
	}
	list_dir_recursive((argc < 2) ? "." : argv[1]);
        return 0;
}
