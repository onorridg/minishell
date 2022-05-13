/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whitespaces_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:16:10 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 19:29:37 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_whitespaces_len(char *string, int flag)
{
	int	i;

	i = 0;
	if (flag == TRUE)
	{
		while (string[i] && (string[i] == '\n' || string[i] == '\t'
				|| string[i] == '\v' || string[i] == '\r' || string[i] == '\f'
				|| string[i] == ' '))
			i++;
	}
	else if (flag == FALSE)
	{
		while (string[i] && (string[i] != '\n' && string[i] != '\t'
				&& string[i] != '\v' && string[i] != '\r' && string[i] != '\f'
				&& string[i] != ' '))
			i++;
	}
	return (i);
}
