/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:35:32 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/11 19:30:05 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void redirect_output_append_mode(t_command *command, int part)
{
	int 	fd;
	char	*file_n;
	
	file_n = command->command_parts[part + 1];
	if (access(file_n, F_OK) != -1 && access(file_n, W_OK) == -1)
		error_redirection_handler(command, file_n);
	else
	{
		fd = open(file_n, O_CREAT | O_WRONLY | O_APPEND, 0666);
		if (fd < 0)
		{
			printf("FCK\n");
			exit(1);
		}
		command->file_pipe[1] = fd;
		rewrite_command_part_arr(command, part);
	}
}

void	here_doc(t_command *command, int part)
{	
	char 	*str;
	char 	*stop;
	int 	i;
	int 	pipe_write;
	
	command->here_doc = TRUE;
	if (command->command_parts[part + 1])
	{	
		get_pipe(command);
		pipe_write = command->file_pipe[1];
		stop = command->command_parts[part + 1];
		while (TRUE)
		{
			str = readline("> ");
			if (!str || ft_strcmp(str, stop))
			{
				close(pipe_write);
				break;
			}
			else
			{
				i = 0;
				write(pipe_write, str, ft_strlen(str));
				write(pipe_write, "\n",  1);
			}
		}
		rewrite_command_part_arr(command, part);
	}
	else 
	{
		printf("syntax error near unexpected token `newline'\n");
		fflush(stdout);
	}
	//fprintf(stderr, "EXIT here_doc\n");
	//fflush(stderr);
}

static void redirection_output(t_command *command, int part)
{	
	int fd;
	char *file_n;
	
	file_n = command->command_parts[part + 1];
	if (access(file_n, F_OK) != -1 && access(file_n, W_OK) == -1)
		error_redirection_handler(command, file_n);
	else 
	{
		fd = open(file_n, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd < 0)
		{
			printf("WTF\n");
			exit(1);
		}
		command->file_pipe[1] = fd;
		rewrite_command_part_arr(command, part);
	}
}

static void redirect_input(t_command *command, int part)
{
	int		fd;
	char	*file_n;
	
	file_n = command->command_parts[part + 1];
	if (access(file_n, F_OK) != -1 && access(file_n, R_OK) == -1)
		error_redirection_handler(command, file_n);
	else 
	{
		fd = open(command->command_parts[part + 1], O_RDONLY, 0777);
		command->file_pipe[0] = fd;
		rewrite_command_part_arr(command, part);
	}
}

void	redirections(t_command *command)
{	
	int part;
	
	part = 0;
	//additional_redirection_parser(command);
	while(command->command_parts && command->command_parts[part] && g_data->error_redirection != FAIL)
	{
		if (ft_strcmp(command->command_parts[part], "<") && command->command_parts[part + 1])
		{
			redirect_input(command, part);
			part = 0;
		}
		else if (ft_strcmp(command->command_parts[part], ">") && command->command_parts[part + 1])
		{
			redirection_output(command, part);
			part = 0;
		}
		else if (ft_strcmp(command->command_parts[part], "<<") && command->command_parts[part + 1])
		{
			here_doc(command, part);
			part = 0;
		}
		else if (ft_strcmp(command->command_parts[part], ">>") && command->command_parts[part + 1])
		{
			redirect_output_append_mode(command, part);
			part = 0;
		}
		else 
			part++;
	}
}