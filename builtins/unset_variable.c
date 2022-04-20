/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:05:48 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/20 17:25:17 by onorridg         ###   ########.fr       */
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
	while (node)
	{	
		save = node;
		if (ft_strcmp(node->variable, string))
		{	
			g_data->first_envp = node->next;
		}
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

int	ft_unset(t_command *command)
{	
	if (command->command_parts[1])
	{
		printf("%s %s\n", command->command_parts[0], command->command_parts[1]);
		if (!unset_envp(&command->command_parts[1][1],
			g_data->first_envp, NULL))
			uset_own_variable(&command->command_parts[1][1],
				g_data->first_var, NULL);
	}
	return (0);
}
