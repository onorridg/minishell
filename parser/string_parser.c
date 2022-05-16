/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:10:04 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 17:48:48 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*value_to_variable(char *string)
{
	char	*value;
	t_envp	*var;

	value = NULL;
	var = g_data->first_envp;
	value = my_getenv(string);
	if (!value)
		value = get_own_env(string);
	if (!value)
		value = ft_set_mem_aloc("");
	free(string);
	return (value);
}

char	*spaces_deleter(char *string)
{
	int		i;
	char	*new_string;

	i = 0;
	while (string[i] && (string[i] == '\n' || string[i] == '\t'
			|| string[i] == '\v' || string[i] == '\r'
			|| string[i] == '\f' || string[i] == ' '))
		i++;
	if (i != 0)
	{
		new_string = ft_set_mem_aloc(&string[i]);
		free(string);
		return (new_string);
	}
	return (string);
}

char	**command_parts_parser(t_command *command)
{
	char	**command_parts;
	int		i;

	command_parts = ft_split(command->command, ' ');
	if (!command_parts)
		return (NULL);
	i = 0;
	while (command_parts[i])
	{	
		command_parts[i] = spaces_deleter(command_parts[i]);
		i++;
	}
	return (command_parts);
}

static t_command	*insert_command_into_node(char *command, char **envp,
	t_command *previous_node_ptr)
{	
	t_command	*node;

	(void)envp;
	node = (t_command *)malloc(sizeof(t_command));
	if (!node)
		exit(1);
	node->command = command;
	node->command_parts = NULL;
	node->last_command = FALSE;
	node->next = NULL;
	node->file_pipe[0] = -1;
	node->file_pipe[1] = -1;
	node->here_doc = FALSE;
	if (previous_node_ptr)
		previous_node_ptr->next = node;
	return (node);
}

t_command	*string_parser(char *string, char **envp)
{	
	t_command	*first_command;
	t_command	*node;
	char		**commands_array;
	int			i;

	commands_array = ft_split(string, '|');
	if (!commands_array)
		return (0);
	i = 0;
	node = NULL;
	while (commands_array[i])
	{
		node = insert_command_into_node(commands_array[i], envp, node);
		if (i == 0)
			first_command = node;
		i++;
	}
	free(commands_array);
	node->last_command = TRUE;
	g_data->command_counter = i;
	return (first_command);
}
