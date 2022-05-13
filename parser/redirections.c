/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:35:32 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 21:46:53 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_output_append_mode(t_command *command, int part, int *i)
{
	int		fd;
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
	*i = 0;
}

void	here_doc(t_command *command, int part, int *i)
{	
	char	*str;
	char	*stop;
	int		pipe_write;

	command->here_doc = TRUE;
	if (command->command_parts[part + 1])
	{	
		get_pipe(command);
		pipe_write = command->file_pipe[1];
		stop = command->command_parts[part + 1];
		heredoc_read(stop, pipe_write);
		rewrite_command_part_arr(command, part);
	}
	else
		write(1, "syntax error near unexpected token `newline'\n", 46);
	*i = 0;
}

static void	redirection_output(t_command *command, int part, int *i)
{	
	int		fd;
	char	*file_n;

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
	*i = 0;
}

static void	redirect_input(t_command *command, int part, int *i)
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
	*i = 0;
}

void	redirections(t_command *command)
{	
	int		part;
	char	*command_part;

	part = 0;
	additional_redirection_parser(command);
	while (command->command_parts && command->command_parts[part]
		&& g_data->error_redirection != FAIL)
	{	
		command_part = command->command_parts[part];
		if (ft_strcmp(command_part, "<") && command->command_parts[part + 1])
			redirect_input(command, part, &part);
		else if (ft_strcmp(command_part, ">") && command->command_parts[part + 1])
			redirection_output(command, part, &part);
		else if (ft_strcmp(command_part, "<<") && command->command_parts[part + 1])
			here_doc(command, part, &part);
		else if (ft_strcmp(command_part, ">>") && command->command_parts[part + 1])
			redirect_output_append_mode(command, part, &part);
		else
			part++;
	}
}
