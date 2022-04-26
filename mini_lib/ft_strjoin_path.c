/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:59:24 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/26 12:39:03 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin_path(char *str1, char *str2)
{   
    char *str_new;
    int len;
    int i;
    int j;
    
    len = 0;
    if (str1)
        len = ft_strlen(str1);
    if (str2)
        len += ft_strlen(str2);
    str_new = (char *)malloc(sizeof(char) * len + 2);
	if (!str_new)
		exit(1);
    i = 0;
    j = 0;
    while (str1[j])
        str_new[i++] = str1[j++];
    j = 0;
    str_new[i++] = '/';
    while (str2[j])
        str_new[i++] = str2[j++];
    str_new[i] = '\0';
    return (str_new);
}