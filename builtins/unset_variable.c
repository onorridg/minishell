/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:05:48 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/15 20:54:08 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	uset_own_variable(char *string, t_own_var *node, t_own_var *save)
{	
	while (node)
	{	
		save = node;
		if (ft_strcmp(node->variable, string))
			g_data->first_var = node->next;
		else if (node->next && ft_strcmp(node->next->variable, string))
		{
			save = node->next;
			node->next = node->next->next;
		}
		if (node != save)
		{
			free(save);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

static int	unset_envp(char *string, t_envp *node, t_envp *save)
{	
	t_envp	*privius;

	if (ft_strcmp(node->variable, string))
	{	
		save = node;
		if (node->next)
			g_data->first_envp = node->next;
		else
		{
			g_data->first_envp = NULL;
			g_data->last_envp = NULL;
		}
		free(save->variable);
		if (save->value)
			free(save->value);
		free(save);
		return (0);
	}
	privius = node;
	node = node->next;
	while (node)
	{	
		save = node;
		if (!node->next && ft_strcmp(node->variable, string))
		{
			privius->next = NULL;
			g_data->last_envp = privius;
			free(save->variable);
			if (save->value)
				free(save->value);
			free(save);
			return (0);
		}
		else if (node->next && ft_strcmp(node->variable, string))
		{
			privius->next = node->next;
			free(save->variable);
			if (save->value)
				free(save->value);
			free(save);
			return (0);
		}
		privius = node;
		node = node->next;
	}
	return (0);
}

int	ft_unset(t_command *command)
{	
	int i;
	
	i = 1;
	if (command->command_parts[0])
	{	
		while (command->command_parts[i])
		{
			if (!unset_envp(command->command_parts[i],
					g_data->first_envp, NULL))
				uset_own_variable(command->command_parts[i],
					g_data->first_var, NULL);
			i++;
		}
	}
	set_exit_code(0);
	return (0);
}
