/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_str_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:07:53 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/21 13:27:51 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_copy_str_len(char *string, int len)
{
	int 	i;
	char 	*new_string;

	new_string = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_string)
		exit(1);
	i = 0;
	while (string[i] && len > 0)
	{
		new_string[i] = string[i];
		i++;
		len--;
	}
	new_string[i] = '\0';
	return (new_string);	
}