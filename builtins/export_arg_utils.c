/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:48:08 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 17:17:27 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_own_envp(char **data, char *variable)
{	
	t_own_var	*var;

	var = g_data->first_var;
	while (var)
	{
		if (ft_strcmp(variable, var->variable))
		{
			if (set_new_env_entry(var->variable, var->value) == 1)
				return (1);
			split_free(data, -1);
			return (0);
		}
		var = var->next;
	}
	return (1);
}

int	get_envp(char **data)
{	
	t_envp		*envp;

	envp = g_data->first_envp;
	while (envp)
	{
		if (ft_strcmp(data[0], envp->variable))
		{
			if (data[1])
				envp->value = data[1];
			else
				envp->value = "";
			free(data[0]);
			free(data);
			return (0);
		}
		envp = envp->next;
	}
	return (1);
}
