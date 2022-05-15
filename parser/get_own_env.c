/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_own_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:25:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/15 17:28:36 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_own_env(char *string)
{	
	t_own_var	*variable;
	char		*value;

	variable = g_data->first_var;
	value = NULL;
	while (variable)
	{
		if (ft_strcmp(string, variable->variable))
		{
			value = ft_set_mem_aloc(variable->value);
			break ;
		}
		variable = variable->next;
	}
	return (value);
}
