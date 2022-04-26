/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:58:11 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/26 17:15:07 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_new_env_entry(char *variable, char *value)
{	
	t_envp	*node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		exit(1);
	node->variable = variable;
	node->value = value;
	node->next = NULL;
	g_data->last_envp->next = node;
	g_data->last_envp = node;
	return (0);
}

static int export_arg(char *variable)
{		
	t_own_var	*var;
	 
	var = g_data->first_var;
	while (var)
	{
		if (ft_strcmp(variable, var->variable))
		{
			set_new_env_entry(var->variable, var->value);
			return (0);
		}
		var = var->next;
	}
	return (1);

}

static void display_export(int command_number)
{
	char	**sorted_envp;
	int		i;
	char    buff[100];
	sorted_envp = alphabet_sort();
	i = 0;
	
	while (sorted_envp[i])
	{	
		write(g_data->pipe_array[command_number][1],  "declare -x ", 11);
		write(g_data->pipe_array[command_number][1], sorted_envp[i], ft_strlen(sorted_envp[i]));
		i++;
		write(g_data->pipe_array[command_number][1], "\n", 2);
	}
	split_free(sorted_envp, -1);
}

int	ft_export(t_command *command)
{	
	int	i;
	
	i = 1;
	if (command->command_parts[i])
	{	
		while (command->command_parts[i])
			export_arg(command->command_parts[i++]);
	}
	else 
		display_export(command->command_number);
	return (0);
}