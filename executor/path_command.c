/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:26 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/28 12:00:39 by onorridg         ###   ########.fr       */
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
		//printf("EXECVE PID!!!!\n");
		//fflush(stdout);
		
		//close(pipe_fds[1]);					
		if (command->command_number == 0) 	
		{			
												//close(pipefds[0]); rewrite, dose not close if << or <
			/*if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			{	
				error_handler(command);
				printf("ERORO DUP@\n");
				write(1, strerror(errno), strlen(strerror(errno)));
				fflush(stdout);
				exit(1);
			}*/
			if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
			{	
				printf("ERORO DUP@\n");
				write(1, strerror(errno), strlen(strerror(errno)));
				fflush(stdout);
				exit(1);
			}
			//printf("loh\n");
			//fflush(stdout);
		}
		else
		{	
			//printf("KEK")
			pipe_fds[0] = g_data->pipe_array[command->command_number - 1][0];
			if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
				exit(1);
			//if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			//	exit(1);
		}
		execve(path, command->command_parts, env_generator());
		printf("loh execve\n");
		fflush(stdout);
		exit(1);
	}
	wait(NULL);
	//close(pipe_fds[1]);
	//close(pipe_fds[0]);	
	return (0);
}

int		path_command(t_command *command)
{	char *path;

	if (ft_strlen(command->command_parts[0]) > 0)
	{	
		parser_quote_and_variable(command);
		path = get_command_path(command);
		if (path)
			execut_comand(command, path);
		else
			execve(command->command_parts[0], command->command_parts, env_generator());
	}
	else
		exec_open_pipe_command(command);

		//printf("error pars last pipe\n");
	return 0;
}