/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_varibale_in_string_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:37:28 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 19:57:58 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_qoute_replace_variable(char *quote, char *str, int i)
{	
	if (str[i] == '\'' || str[i] == '"')
	{
		if (*quote == 0)
			*quote = str[i];
		else if (*quote == str[i])
			*quote = 0;
		return (1);
	}
	return (0);
}

void	free_replace_variable(char *new_string, char *left_part,
	char *value, char *right_part)
{
	free(new_string);
	free(left_part);
	free(value);
	free(right_part);
}
