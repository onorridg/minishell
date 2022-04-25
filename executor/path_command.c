/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:26 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/25 12:39:13 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void execut_comand(t_command *command, char *path)
{	
	int		*pipe_fds;
	pid_t	pid;
	
	
	execve(path, command->command_parts, env_generator());
	exit(1);
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