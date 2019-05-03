/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:10:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/05/03 15:11:04 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
    #include <dirent.h>

    int main (int c, char *v[]) {
        int len;
        struct dirent *pDirent;
        DIR *pDir;

        if (c < 2) {
            printf ("Usage: testprog <dirname>\n");
            return 1;
        }
        pDir = opendir (v[1]);
        if (pDir == NULL) {
            printf ("Cannot open directory '%s'\n", v[1]);
            return 1;
        }

        while ((pDirent = readdir(pDir)) != NULL) {
            printf ("[%s]\n", pDirent->d_name);
        }
        closedir (pDir);
        return 0;
    }
