/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:26 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/25 15:07:03 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static void execute_command_with_redirection(t_command *command, char *path)
{
	
}*/

static void execut_comand(t_command *command, char *path)
{	
	int		*pipe_fds;
	pid_t	pid;
	
	execve(path, command->command_parts, env_generator());
	exit(1);
}

void	command_part_parser(t_command *command)
{
	int i;	
	char *new_string;
	
	i = 0;
	while (command->command_parts[i])
	{	
		//printf("command part: %s\n", command->command_parts[i]);
		//new_string = quote_deleter(command->command_parts[i]);
		/*if (new_string)
		{	
			free(command->command_parts[i]);
		}*/
		command->command_parts[i] = new_string;
		i++;
	}	
}

int		path_command(t_command *command)
{	char *path;

	if (ft_strlen(command->command_parts[0]) > 0)
	{	
		//command_part_parser(command);
		path = get_command_path(command);
		if (path)
			execut_comand(command, path);
	}
	else
		printf("error pars last pipe\n");
	return 0;
}