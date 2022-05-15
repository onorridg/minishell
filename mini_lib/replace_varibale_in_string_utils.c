/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_varibale_in_string_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:37:28 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/15 15:58:06 by onorridg         ###   ########.fr       */
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
	if (new_string)
		free(new_string);
	if (left_part)
		free(left_part);
	if (value)
		free(value);
	if (right_part)
		free(right_part);
}
