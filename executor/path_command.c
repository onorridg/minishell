/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:26 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/11 18:31:58 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    parser_quote_and_variable(t_command *command)
{
	int 	i;
	int 	replace;

	i = 0;
	while (command->command_parts[i])
	{
		command->command_parts[i] = inser_value_to_string(command->command_parts[i]);
		command->command_parts[i] = quote_parse(command->command_parts[i]); //quote_deleter(command->command_parts[i]);
		i++;
	}
	redirections(command);
}

static int execut_comand(t_command *command, char *path)
{
	int *pipe_fds;
	pid_t pid;
	int stt;

	pipe_fds = g_data->pipe_array[command->command_number];
	pid = fork();
	if (pid == -1)
		exit(1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_DFL);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if ((command->file_pipe[1] < 0 || command->here_doc == TRUE) && command->last_command == FALSE) 
		{
			if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
				exit(1);
		}
		else if (command->file_pipe[1] > 0 && command->here_doc == FALSE)
		{
			if (dup2(command->file_pipe[1], STDOUT_FILENO) == -1)
				exit(1);
			// if (command->file_pipe[1] > 0 )
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
		execve(path, command->command_parts, env_generator());
		exit(127);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &stt, 0);
	//signal(SIGINT, hdl_child_sigint);
	//signal(SIGQUIT, hdl_child_sigquit);
	set_signal_configuration();
	if (WIFEXITED(stt))
	{
		//g_data->exit_code = WEXITSTATUS(stt);
		g_data->exit_code = stt;
		if (g_data->exit_code != 0)
		{	
			g_data->error_command = FAIL;
			if (access(path, X_OK) == -1)
			{
				write(1, "minishell: ", 11);
				write(1, command->command_parts[0], strlen(command->command_parts[0]));
				write(1, ": command not found\n", 20);
			}
			//close(g_data->pipe_array[command->command_number][0]);
		}
		//printf("exit_code: %i\n", g_data->exit_code);
		set_exit_code(g_data->exit_code);
	}
	else if (WTERMSIG(stt))
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
	if (command->file_pipe[0] != -1)
		close(command->file_pipe[0]);
	if (command->file_pipe[1] != -1)
		close(command->file_pipe[1]);
	close(pipe_fds[1]);
	return (0);
}

int path_command(t_command *command)
{
	char *path;

	if (command->command_parts[0] && ft_strlen(command->command_parts[0]) > 0)
	{
		//parser_quote_and_variable(command);
		//printf("OUT parsing\n");
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
		// execve(command->command_parts[0], command->command_parts, env_generator());
	}
	else
	{
		printf("open pipe\n[!] Now blocked\n");
		fflush(stdout);
		// exec_open_pipe_command(command);
	}
	// if (g_data->exit_code != 0) mb needed exit code upper 120 ???
	//	error_handler(command);
	return 0;
}