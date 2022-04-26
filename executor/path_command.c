/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:26 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/26 15:23:59 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



static void	command_part_parser(t_command *command)
{
	int i;	
	char *new_string;
	
	i = 0;
	while (command->command_parts[i])
	{	
		//new_string = inser_value_to_string(command->command_parts[i]);
		new_string = quote_deleter(command->command_parts[i]);
		if (new_string)
		{	
			free(command->command_parts[i]);
			command->command_parts[i] = new_string;
		}
		i++;
	}	
}

static void command_part_replace_vriable(t_command *command)
{
	int	i;
	int j;
	
	i = 0;
	while (command->command_parts[i])
	{	
		j = 0;
		while (command->command_parts[i][j])
		{
			if (command->command_parts[i][j] == '$')
			{
				return;	
			}
		}
		i++;
	}
	
}

/*static void execute_command_with_redirection(t_command *command, char *path)
{
	
}*/

/*static void execut_comand(t_command *command, char *path)
{	
	int		*pipe_fds;
	pid_t	pid;
	
	execve(path, command->command_parts, env_generator());
	exit(1);
}*/

static int execut_comand(t_command *command, char *path)
{	
	int		*pipe_fds;
	pid_t	pid;
	char	output[1];
	
	pipe_fds = g_data->pipe_array[command->command_number];
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{	
		close(pipe_fds[0]);						
			if (command->command_number == 0) 	
			{													//close(pipefds[0]); rewrite, dose not close if << or <
				if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
					exit(1);
			}
			else
			{
				pipe_fds[0] = g_data->pipe_array[command->command_number - 1][0];
				if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
					exit(1);
				if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
					exit(1);
			}
		execve(path, command->command_parts, env_generator());
		exit(1);
	}
	//close(pipe_fds[1]);
	//close(pipe_fds[0]);	
	return (0);
}

int		path_command(t_command *command)
{	char *path;

	if (ft_strlen(command->command_parts[0]) > 0)
	{	
		command_part_parser(command);
		path = get_command_path(command);
		if (path)
			execut_comand(command, path);
		else
			execve(command->command_parts[0], command->command_parts, env_generator());
	}
	else
		printf("error pars last pipe\n");
	return 0;
}