/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:59:24 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/16 14:21:09 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return i;
}

char *ft_strjoin(char *str1, char *str2)
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