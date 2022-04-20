/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:33:05 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/20 16:27:54 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_command *command)
{
	t_envp 	*variable_node;

	variable_node = g_data->first_envp;
	while (variable_node)
	{
		write(1, variable_node->variable, ft_strlen(variable_node->variable));
		write(1, "=", 1);
		write(1, variable_node->value, ft_strlen(variable_node->value));
		write(1, "\n", 1);
		variable_node = variable_node->next;	
	}
	return (0);
}

// allowed alphabet, numbers but not like as first character in name
int	set_variable(char *string, t_own_var *last_var)	
{
	char		**data;
	t_own_var *swap;
	int			i;
	
	data = ft_split(string, '=');
	if (data && data[1] && !data[2] && ft_strlen(data[i]) <= LINE_MAX - 1)
	{
		if ((data[0][0] >= 'A' && data[0][0] <= 'Z') ||
			(data[0][0] >= 'a' && data[0][0] <= 'z') || data[0][0] == '_')
		{	
			i = 0;
			while ((data[0][i] >= 'A' && data[0][i] <= 'Z')
				|| (data[0][i] >= 'a' && data[0][i] <= 'z')
				|| data[0][i] == '_'
				|| (data[0][i] >= '0' && data[0][i] <= '9'))
				i++;
			if (!data[0][i])
			{	
				swap = g_data->last_var;
				g_data->last_var = (t_own_var *)malloc(sizeof(t_own_var));
				if (!g_data->last_var)
					exit(1);
				g_data->last_var->variable = data[0];
				g_data->last_var->value = data[1];
				g_data->last_var->next = NULL;
				if (!g_data->first_var)
					g_data->first_var = g_data->last_var;
				else 
					swap->next = g_data->last_var;
			}
			else
				printf("[!] Incorrect name variable\n");		//change this error to error like in bash
		}
		else
			printf("[!] Incorrect name variable\n"); 		//change this error to error like in bash
	}	
	return (0);
}