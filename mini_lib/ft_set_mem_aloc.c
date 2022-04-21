/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_mem_aloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:40:57 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/21 17:14:44 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_set_mem_aloc(char *string)
{
	int i;
	char *aloc_mem;

	aloc_mem = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
	if (!aloc_mem)
		exit(1);
	i = 0;
	while (string[i])
	{
		aloc_mem[i] = string[i];
		i++;
	}
	aloc_mem[i] = '\0';
	return (aloc_mem);
}