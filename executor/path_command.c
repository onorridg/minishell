/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:26 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/23 17:42:30 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static int execut_comand(t_command *command, char *path)
{	
	int		*pipe_fds;
	pid_t	pid;
	char	output[1];

	pipe_fds = g_data->pipe_array[command->command_number];
	//printf("pipe fds: [%i]-[%i]\n", pipe_fds[0], pipe_fds[1]);
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
		//printf("command arg: %s\n", command->command_parts[1]);
		execve(path, command->command_parts, NULL);
		exit(1);
	}
	close(pipe_fds[1]);
	if (command->last_command)
	{
		while (read(pipe_fds[0], output, 1))
			write(1, output, 1);
		close(pipe_fds[0]);
	}
	return (0);
}*/

static int execut_comand(t_command *command, char *path)
{	
	int		*pipe_fds;
	pid_t	pid;
	
	
	execve(path, command->command_parts, NULL);
	exit(1);
	
	
	return (0);
}

int		path_command(t_command *command)
{	char *path;

	if (ft_strlen(command->command_parts[0]) > 0)
	{
		path = get_command_path(command);
		if (path)
			execut_comand(command, path);
	}
	else
		printf("error pars last pipe\n");
	//printf("TEST bash\n");
	return 0;
}