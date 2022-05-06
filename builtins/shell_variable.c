/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:33:05 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/06 18:06:12 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_command *command)
{
	t_envp	*variable_node;
	int		w_pipe;

	w_pipe = g_data->pipe_array[command->command_number][1];
	variable_node = g_data->first_envp;
	while (variable_node)
	{
		write(w_pipe, variable_node->variable, ft_strlen(variable_node->variable));
		write(w_pipe, "=", 1);
		if (variable_node->value)
			write(w_pipe, variable_node->value, ft_strlen(variable_node->value));
		write(w_pipe, "\n", 1);
		variable_node = variable_node->next;
	}
	close(w_pipe);
	return (0);
}

void	set_data_to_variable(char **data)
{	
	t_own_var	*swap;

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

int	set_env_variable(char **data)
{
	t_envp		*envp;
	t_own_var	*own_envp;
	char		*clear_data;

	envp = g_data->first_envp;
	while (envp)
	{
		if (ft_strcmp(envp->variable, data[0]))
		{
			clear_data = envp->value;
			envp->value = ft_set_mem_aloc(data[1]);
			free(clear_data);
			split_free(data, -1);
			return (1);
		}
		envp = envp->next;
	}
	own_envp = g_data->first_var;
	while (own_envp)
	{
		if (ft_strcmp(own_envp->variable, data[0]))
		{
			clear_data = own_envp->value;
			own_envp->value = ft_set_mem_aloc(data[1]);
			free(clear_data);
			split_free(data, -1);
			return (1);
		}
		own_envp = own_envp->next;
	}
	return (0);
}

static void	print_local_err(char *string)
{
	g_data->exit_code = 127;
	write(1, "minishell: ", 12);
	write(1, string, ft_strlen(string));
	write(1, ": command not found\n", 21);
}

/* allowed alphabet, numbers (but not like as first character in name) */

int	set_variable(char *string)
{
	char		**data;

	data = ft_split(string, '=');
	if (!data)
		exit(1);
	if (set_env_variable(data))
		return (0);
	else if (data && data[1] && !data[2] && ft_strlen(data[1]) <= LINE_MAX - 1)
	{
		if (((data[0][0] >= 'A' && data[0][0] <= 'Z') ||
			(data[0][0] >= 'a' && data[0][0] <= 'z') || data[0][0] == '_')
			&& !data[0][ft_char_len(data[0], TRUE)])
			set_data_to_variable(data);
		else
			errno = 255;
	}
	if (errno == 255)
	{	
		split_free(data, -1);
		print_local_err(string);
	}
	return (0);
}
