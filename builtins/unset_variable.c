/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:05:48 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/20 13:32:16 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int uset_own_variable(char *string)
{	
	t_shell_var	*node;
	t_shell_var	*privius_node;

	node = g_data->first_var;
	privius_node = NULL;
	while (node)
	{
		if (ft_strcmp(node->variable, string))
		{	
			if (!privius_node && !node->next)
			{	
				g_data->first_var = NULL;
				g_data->last_envp = NULL;
			}
			else if (!privius_node)
				g_data->first_var = node->next;
			else if (!node->next)
				g_data->last_var = privius_node;
			else 
				privius_node->next = node->next;
			free(node);
			return (1);
		}
		privius_node = node;
		node = node->next;
	}
	return (0);
}

static int unset_envp(char *string)
{
	t_envp 	*node;
	t_envp 	*privius_node;
	
	node = g_data->first_envp;
	privius_node = NULL;
	while (node)
	{	
		if (ft_strcmp(node->variable, string))
		{	
			if (!privius_node && !node->next)
			{
				g_data->first_envp = NULL;
				g_data->last_envp = NULL;
			}
			else if (!privius_node)
				g_data->first_envp = node->next;
			else if (!node->next)
				g_data->last_envp = privius_node;
			else 
				privius_node->next = node->next;
			return (1);
		}
		privius_node = node;
		node = node->next;	
	}
	return (0);
}

int	unset_variable(char *string)
{
	if (!unset_envp(string))
		uset_own_variable(string);
	return (0);
}