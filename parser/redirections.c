/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:35:32 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/29 16:00:56 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static void redirection_out_append(t_command * command)
{
	int		fd;
	char 	buf[1];
	int 	read_ch;
	int		file_pipe_write;
	
	if (command->command_parts[part + 1])
	{	
		//pipe(pipe_fds);
		get_file_pipe(command);
		file_pipe_write = command->file_pipe[1];
		fd = open(command->command_parts[part + 1], O_RDONLY, 0777);
		//printf("file fd: %i\n", fd);
		if (fd == -1)
		{	
			printf("[!] ERROR\n");
			error_handler(command);
			exit(1);
		}
		while (read(fd, buf, 1) >= 0)
		{	
			//printf("|%c|\n", buf[0]);
			//fflush(stdout);
			if (buf[0] == '\0')
				break;
			write(file_pipe_write, buf, 1);
			buf[0] = 0;
		}
		close(fd);
		close(file_pipe_write);
		rewrite_command_part_arr(command, part);
	}
	else 
	{
		printf("syntax error near unexpected token `newline'\n");
		fflush(stdout);
	}
}*/

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

static void redirect_input(t_command *command, int part)
{	
	int		fd;
	
	fd = open(command->command_parts[part + 1], O_RDONLY, 0777);
	command->file_pipe[0] = fd;
	rewrite_command_part_arr(command, part);
}

void	here_doc(t_command *command, int part)
{	
	char 	*str;
	char 	*stop;
	int 	i;
	int 	pipe_write;
	
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

void	redirections(t_command *command)
{	
	int part;
	
	part = 0;
	while(command->command_parts[part])
	{
		if (ft_strcmp(command->command_parts[part], "<"))
		{
			redirect_input(command, part);
			part = 0;
		}
		else if (ft_strcmp(command->command_parts[part], "<<"))
		{
			here_doc(command, part);
			part = 0;
		}
		else 
			part++;
	}
	//printf("REDIRECTION OUT\n");
	//fflush(stdout);
}