/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:26 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/04 13:16:31 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	parser_quote_and_variable(t_command *command)
{
	int i;	
	char *new_string;
	int	replace;
	
	i = 0;
	while (command->command_parts[i])
	{	
		replace = TRUE;
		if (command->command_parts[i][0] == '\'')
			replace = FALSE;
		new_string = quote_deleter(command->command_parts[i]);
		if (new_string)
			command->command_parts[i] = new_string;
		if (replace)
		{
			new_string = inser_value_to_string(command->command_parts[i]);
			//printf("value: |%s|\n", new_string);
			//fflush(stdout);
			command->command_parts[i] = new_string;
		}
		i++;
	}
	redirections(command);
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

static int execut_comand(t_command *command, char *path)
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
		if ((command->file_pipe[1] < 0 || command->here_doc == TRUE) && command->last_command == FALSE) //
		{
			if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
				exit(1);
		}
		else if (command->file_pipe[1] > 0 && command->here_doc == FALSE)
		{
			if (dup2(command->file_pipe[1], STDOUT_FILENO) == -1)
				exit(1);
			//if (command->file_pipe[1] > 0 )
			close(pipe_fds[1]);
		}
		
		if (command->command_number > 0)
				pipe_fds[0] = g_data->pipe_array[command->command_number - 1][0];
		if (command->file_pipe[0] < 0)
		{
			if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
				exit(1);
		}
		else
		{
			if (dup2(command->file_pipe[0], STDIN_FILENO) == -1)
				exit(1);
		}
		execve(path, command->command_parts, env_generator());
		exit(1);
	}
	//wait(NULL);
	waitpid(pid, &stt, 0);
	if (WIFEXITED(stt))
	{
		g_data->exit_code = WEXITSTATUS(stt);
		set_exit_code(g_data->exit_code);
	}
	if (command->file_pipe[0] != -1)
		close(command->file_pipe[0]);
	if (command->file_pipe[1] != -1)
		close(command->file_pipe[1]);
	close(pipe_fds[1]);
	return (0);
}

int		path_command(t_command *command)
{	char *path;

	if (ft_strlen(command->command_parts[0]) > 0)
	{	
		//fprintf(stderr, "IN PARSE QUOTE\n");
		//fflush(stderr);
		parser_quote_and_variable(command);
		//fprintf(stderr, "OUT PARSE QUOTE\n");
		//fflush(stderr);
		if (g_data->error_status == FAIL)
			return (1);
		path = get_command_path(command);
		if (path)
			execut_comand(command, path);
		else
			execut_comand(command, command->command_parts[0]);
			//execve(command->command_parts[0], command->command_parts, env_generator());
	}
	else
	{	
		printf("open pipe\n");
		fflush(stdout);
		exec_open_pipe_command(command);
	}

		//printf("error pars last pipe\n");
	return 0;
}