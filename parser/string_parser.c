/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:10:04 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/18 18:16:07 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	value_to_variable(char *string)
{
	return;
}

char	**command_parts_parser(t_command *command)
{
	BUILTIN	**builtin_functions;
	int		builtin_number;
	char	**command_parts;
	t_data	*data;
	
	data = (t_data *)malloc(sizeof(t_data));
	builtin_functions = set_ptr_func_to_arr();
	command_parts = ft_split(command->command, ' ');
	if(!command_parts)
		exit(1);
	builtin_number = builtin_chek(command_parts[0]);
	if (builtin_number == ECHO)
	{	
		printf("%s\n", command->command);
	}
	else if (builtin_number != BASH)
	{
		if (!command_parts[1]) 								// check options
			builtin_functions[builtin_number](command->envp);
		else
			printf("[!] Error options\n");   				// print error message
	}
	else
	{
		printf("BASH: %s\n", command->command);
	}
	free(data);
	return 0;
}

static t_command	*insert_command_into_node(char *command, char **envp, t_command *previous_node_ptr)
{	
	t_command	*node;
	
	node = (t_command *)malloc(sizeof(t_command));
	if (!node)
		exit(1);
	node->command = command;
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