/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_mem_aloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:40:57 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 15:47:44 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_set_mem_aloc(char *string)
{
	int		i;
	char	*aloc_mem;
	int		len;

	len = ft_strlen(string);
	aloc_mem = (char *)malloc(sizeof(char) * (len + 1));
	if (!aloc_mem)
		exit(1);
	i = 0;
	while (string && string[i])
	{
		aloc_mem[i] = string[i];
		i++;
	}
	aloc_mem[i] = '\0';
	return (aloc_mem);
}
