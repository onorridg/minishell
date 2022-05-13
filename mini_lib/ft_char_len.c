/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:48:54 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 18:53:00 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_char_len(char *string, int flag)
{
	int	i;

	i = 0;
	if (flag == TRUE)
	{
		while (string[i] && ((string[i] >= 'A' && string[i] <= 'Z')
				|| (string[i] >= 'a' && string[i] <= 'z')
				|| (string[i] >= '0' && string[i] <= '9')
				|| string[i] == '_'))
			i++;
	}
	else if (flag == FALSE)
	{
		while (string[i] && ((string[i] <= 'A' && string[i] >= 'Z')
				&& (string[i] <= 'a' && string[i] >= 'z')
				&& (string[i] <= '0' && string[i] >= '9')
				&& string[i] != '_'))
			i++;
	}
	return (i);
}
