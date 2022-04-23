/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:26 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/23 12:17:15 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int execut_comand(t_command *command, char *path)
{	
	int		pipefds[2];
	pid_t	pid;
	char	output[1];

	if (pipe(pipefds) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(pipefds[0]);
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			exit(1);
		execve(path, command->command_parts, NULL);
		exit(1);
	}
	close(pipefds[1]);
	//if (dup2(pipefds[0], STDIN_FILENO) == -1)
	//	exit(1);
	while (read(pipefds[0], output, 1))
		write(1, output, 1);
	close(pipefds[0]);
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
	//else
	//	print("error pipe\n")
	//printf("TEST bash\n");
	return 0;
}