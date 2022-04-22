/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:16:21 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/22 18:08:51 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(char *variable)
{		
	t_envp	*var;
	char	*value;
	 
	var = g_data->first_envp;
	value = NULL;
	while (var)
	{
		if (ft_strcmp(variable, var->variable))
		{
			value = ft_set_mem_aloc(var->value);
			break;
		}
		var = var->next;
	}
	return (value);
}