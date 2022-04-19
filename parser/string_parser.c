/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:10:04 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/19 12:10:24 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*	
	
*/


char	*value_to_variable(char *string)
{
	char 	*value;
	char	*env_variable;
	int		i;

	env_variable = getenv(&string[1]);
	if (env_variable)
	{
		value = (char *)malloc(sizeof(char) * ft_strlen(env_variable + 1));
		i = 0;
		while (env_variable[i])
		{
			value[i] = env_variable[i];
			i++;
		}
		value[i] = '\0';
	}
	else
	{
		value = (char *)malloc(sizeof(char) * 2);
		value[0] = ' ';
		value[1] = '\0';
	}
	//printf("%s=%s\n", string, value);
	//free(string);
	return (value);
}

char	*spaces_deleter(char *string)
{
	int 	i;
	char	*new_string;
	
	i = 0;
	while (string[i] == '\n' || string[i] == '\t' || string[i] == '\v'
		|| string[i] == '\r' || string[i] == '\f' || string[i] == ' ')
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
	if(!command_parts)
		exit(1);
	i = 0;
	while(command_parts[i])
	{
		command_parts[i] = spaces_deleter(command_parts[i]);
		//printf("%s\n", command_parts[i]);
		if(command_parts[i][0] == '$' && ft_strlen(command_parts[i]) > 1)
			command_parts[i] = value_to_variable(command_parts[i]);
		i++;
	}
	return command_parts;
}

static t_command	*insert_command_into_node(char *command, char **envp, t_command *previous_node_ptr)
{	
	t_command	*node;
	
	node = (t_command *)malloc(sizeof(t_command));
	if (!node)
		exit(1);
	node->command = command;
	node->command_parts = NULL;
	node->envp = envp;
	node->next = NULL;
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
	/*while(first_command)
	{
		printf("%s\n", first_command->command);
		first_command = first_command->next;
	}*/
	return (first_command);
}

/*int main(void)
{
	char *string = readline("$> ");
	string_parser(string, NULL);
	return 0;
}*/