/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:58:11 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/05 12:55:21 by onorridg         ###   ########.fr       */
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
	t_envp		*envp;	
	t_own_var	*var;
	char		**data;

	data = ft_split(variable, '=');
	envp = g_data->first_envp;
	while (data[1] && ft_strlen(data[1]) > 0 && envp)
	{
		if (ft_strcmp(data[0], envp->variable))
		{
			envp->value = data[1];
			free(data[0]);
			free(data);
			return (0);
		}
		envp = envp->next;
	}
	var = g_data->first_var;
	while (var)
	{
		if (ft_strcmp(variable, var->variable))
		{
			set_new_env_entry(var->variable, var->value);
			split_free(data, -1);
			return (0);
		}
		var = var->next;
	}
	if (data[0] && data[1] && ft_strlen(data[1]) > 0)
		set_new_env_entry(data[0], data[1]);
	free(data);
	return (0);

}

static void display_export(int command_number)
{
	char	**sorted_envp;
	int		i;
	int		pipe;

	pipe = g_data->pipe_array[command_number][1];
	sorted_envp = alphabet_sort();
	i = 0;
	while (sorted_envp[i])
	{	
		write(pipe,  "declare -x ", 11);
		write(pipe, sorted_envp[i], ft_strlen(sorted_envp[i]));
		i++;
		write(pipe, "\n", 1);
	}
	split_free(sorted_envp, -1);
}

int	ft_export(t_command *command)
{	
	int	i;
	
	i = 1;
	if (command->command_parts[i])
	{	
		parser_quote_and_variable(command);
		while (command->command_parts[i])
			export_arg(command->command_parts[i++]);
	}
	else 
		display_export(command->command_number);
	return (0);
}