/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:29:30 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/11 14:33:56 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strcmp(char *str1, char *str2)
{
	int i;
	int com_len;
	
	i = 0;
	com_len = ft_strlen(str2);
	while(str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	//printf("str -> |%s| - |%s| <- stop\n", str1, str2);
	if (i != com_len)
		return (0);
	return (1);
}