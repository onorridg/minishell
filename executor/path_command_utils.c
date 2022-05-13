/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:15:29 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 18:39:22 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fork_pipe(t_command *command, int *pipe_fds)
{
	if (command->file_pipe[0] != -1)
		close(command->file_pipe[0]);
	if (command->file_pipe[1] != -1)
		close(command->file_pipe[1]);
	close(pipe_fds[1]);
}

void	set_fork_signal(int flag)
{
	if (flag == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (flag == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	get_status_code_signal(int stt)
{
	if (stt == 2)
	{	
		hdl_child_sigint(stt);
		set_exit_code(130);
	}
	else if (stt == 3)
	{
		hdl_child_sigquit(stt);
		set_exit_code(131);
	}
}

void	get_status_code(int stt, char *path, t_command *command)
{
	set_exit_code(WEXITSTATUS(stt));
	if (WEXITSTATUS(stt) != 0)
	{	
		g_data->error_command = FAIL;
		if (access(path, X_OK) == -1)
		{
			write(1, "minishell: ", 11);
			write(1, command->command_parts[0],
				strlen(command->command_parts[0]));
			write(1, ": command not found\n", 20);
		}
	}
}

void	set_pipe_config(t_command *command, int *pipe_fds)
{	
	if ((command->file_pipe[1] < 0 || command->here_doc == TRUE)
		&& command->last_command == FALSE)
	{
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			exit(1);
	}
	else if (command->file_pipe[1] > 0 && command->here_doc == FALSE)
	{
		if (dup2(command->file_pipe[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipe_fds[1]);
	}
	if (command->command_number > 0)
		pipe_fds[0] = g_data->pipe_array[command->command_number - 1][0];
	if (command->file_pipe[0] < 0 && command->command_number > 0)
	{
		if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
			exit(1);
	}
	else if (command->file_pipe[0] > 0)
	{
		if (dup2(command->file_pipe[0], STDIN_FILENO) == -1)
			exit(1);
	}
}
