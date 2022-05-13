/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:26 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 19:36:53 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser_quote_and_variable(t_command *command)
{
	int	i;
	int	replace;

	i = 0;
	while (command->command_parts[i])
	{
		command->command_parts[i] = inser_value_to_string(
				command->command_parts[i], 0, 0, 0);
		command->command_parts[i] = quote_parse(command->command_parts[i]);
		i++;
	}
	redirections(command);
}

static int	execut_comand(t_command *command, char *path)
{
	int		*pipe_fds;
	pid_t	pid;
	int		stt;

	pipe_fds = g_data->pipe_array[command->command_number];
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		set_fork_signal(0);
		set_pipe_config(command, pipe_fds);
		execve(path, command->command_parts, env_generator());
		exit(127);
	}
	set_fork_signal(1);
	waitpid(pid, &stt, 0);
	set_signal_configuration();
	if (WIFEXITED(stt))
		get_status_code(stt, path, command);
	else if (WTERMSIG(stt))
		get_status_code_signal(stt);
	close_fork_pipe(command, pipe_fds);
	return (0);
}

int	path_command(t_command *command)
{
	char	*path;

	if (command->command_parts[0] && ft_strlen(command->command_parts[0]) > 0)
	{
		if (!command->command_parts)
			return (1);
		if (g_data->error_command == FAIL || g_data->error_redirection == FAIL)
		{
			close(g_data->pipe_array[command->command_number][1]);
			return (1);
		}
		path = get_command_path(command);
		if (path)
			execut_comand(command, path);
		else
			execut_comand(command, command->command_parts[0]);
		free(path);
	}
	else
	{
		printf("open pipe\n[!] Now blocked\n");
		fflush(stdout);
	}
	return (0);
}
