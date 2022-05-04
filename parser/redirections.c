/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:35:32 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/04 14:49:53 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void error_redirection_handler(t_command *command, char *file_n)
{
	g_data->error_status = FAIL;
	g_data->exit_code = 1;
	set_exit_code(g_data->exit_code);
	write(1, "minishell: ", 11);
	write(1, file_n, ft_strlen(file_n));
	write(1, ": ", 2);
	write(1, strerror(errno), strlen(strerror(errno)));
	write(1, "\n", 1);
}

static char **alloc_mem_for_arr(char **array)
{
	int 	len;
	char	**new_arr;
	
	len = 0;
	while (array[len])
		len++;
	new_arr = (char **)malloc(sizeof(char *) * (len * 10));
	if (!new_arr)
		exit(1);
	return (new_arr);
}

static void rewrite_command_part_arr(t_command *command, int part)
{
	int i;
	int k;
	char **new_arr;
	
	i = 0;
	new_arr = alloc_mem_for_arr(command->command_parts);
	while (command->command_parts[i] && i < part )
	{
		new_arr[i] = command->command_parts[i];
		i++;
	}
	free(command->command_parts[i]);
	free(command->command_parts[i + 1]);
	k = i + 2;
	while(command->command_parts[k])
		new_arr[i++] = command->command_parts[k++];
	free(command->command_parts);
	new_arr[i] = NULL;
	command->command_parts = new_arr;
}

static void get_pipe(t_command *command)
{	
	int pipe_fds[2];
	
	if (pipe(pipe_fds) == -1)
	{	
		printf("new pipe fail\n");
		fflush(stdout);
		exit(1);
	}
	if (command->file_pipe[0] != -1)
		close(command->file_pipe[0]);
	command->file_pipe[0] = pipe_fds[0];
	command->file_pipe[1] = pipe_fds[1];

}

void redirect_output_append_mode(t_command *command, int part)
{
	int 	fd;
	char	*file_n;
	
	file_n = command->command_parts[part + 1];
	if (access(file_n, 0) != -1 && access(file_n, 2) == -1)
		error_redirection_handler(command, file_n);
	else
	{
		fd = open(file_n, O_WRONLY | O_APPEND, 0666);
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
}

static void redirection_output(t_command *command, int part)
{	
	int fd;
	char *file_n;
	
	file_n = command->command_parts[part + 1];
	if (access(file_n, 0) != -1 && access(file_n, 2) == -1)
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
	if (access(file_n, 0) == -1 || access(file_n, 3) == -1)
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
	while(command->command_parts[part] && g_data->error_status != FAIL)
	{
		if (ft_strcmp(command->command_parts[part], "<"))
		{
			redirect_input(command, part);
			part = 0;
		}
		else if (ft_strcmp(command->command_parts[part], ">"))
		{
			redirection_output(command, part);
			part = 0;
		}
		else if (ft_strcmp(command->command_parts[part], "<<"))
		{
			here_doc(command, part);
			part = 0;
		}
		else if (ft_strcmp(command->command_parts[part], ">>"))
		{
			redirect_output_append_mode(command, part);
			part = 0;
		}
		else 
			part++;
	}
	//printf("REDIRECTION OUT\n");
	//fflush(stdout);
}