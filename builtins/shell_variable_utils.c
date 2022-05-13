/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variable_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:21:29 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 17:42:44 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	set_my_env_variable(char **data)
{	
	char		*clear_data;
	t_own_var	*own_envp;

	own_envp = g_data->first_var;
	while (own_envp)
	{
		if (ft_strcmp(own_envp->variable, data[0]))
		{
			clear_data = own_envp->value;
			own_envp->value = ft_set_mem_aloc(data[1]);
			free(clear_data);
			split_free(data, -1);
			return (0);
		}
		own_envp = own_envp->next;
	}
	return (1);
}
