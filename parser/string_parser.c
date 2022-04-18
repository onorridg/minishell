/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:10:04 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/18 17:15:17 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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