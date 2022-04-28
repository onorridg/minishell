/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:35:32 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/28 12:10:30 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	//free(command->command_parts[i]);
	//free(command->command_parts[i + 1]);
	k = i + 2;
	while(command->command_parts[k])
		new_arr[i++] = command->command_parts[k++];
	//free(command->command_parts);
	new_arr[i] = NULL;
	command->command_parts = new_arr;
	i = 0;
	/*while (command->command_parts[i])
		printf("part: %s\n", command->command_parts[i++]);
	fflush(stdout);*/
	
}

static void	set_new_pipe(t_command *command)
{	
	int pipe_fds[2];
	
	close(g_data->pipe_array[command->command_number][0]);
	close(g_data->pipe_array[command->command_number][1]);
	if (pipe(pipe_fds) == -1)
	{	
		printf("new pipe fail\n");
		fflush(stdout);
		exit(1);
	}
	//printf("number command: %i\n", command->command_number);
	g_data->pipe_array[command->command_number][0] = pipe_fds[0];
	g_data->pipe_array[command->command_number][1] = pipe_fds[1];
}

static void redirect_input(t_command *command, int part)
{	
	int		fd;
	char 	buf[1];
	int 	read_ch;
	int		*pipe_fds;
	
	read_ch = 1;
	if (command->command_parts[part + 1])
	{	
		pipe_fds = g_data->pipe_array[command->command_number];
		//printf("pipe[%i][%i]\n", pipe_fds[0], pipe_fds[1]);
		set_new_pipe(command);
		pipe_fds = g_data->pipe_array[command->command_number];
		//printf("pipe[%i][%i]\n", pipe_fds[0], pipe_fds[1]);
		//fflush(stdout);
		fd = open(command->command_parts[part + 1], O_RDONLY);
		//printf("file fd: %i\n", fd);
		if (fd == -1)
		{	
			printf("[!] ERROR\n");
			error_handler(command);
		}
		while (read(fd, buf, 1) > 0)
		{	
			write(pipe_fds[1], buf, 1);
			buf[0] = 0;
		}
		//write(pipe_fds[1], "\0", 1);
		close(fd); 
		close(pipe_fds[1]);
		rewrite_command_part_arr(command, part);
		//printf("KEK\n");
		//fflush(stdout);
		/*fd=0;
		while (command->command_parts[fd])
		{
			printf("parts: %s\n", command->command_parts[fd++]);
			fflush(stdout);
		}*/
	}
	else 
	{
		printf("syntax error near unexpected token `newline'\n");
		fflush(stdout);
	}
}

void	heredoc_r(t_command *command, int part)
{	
	char 	*str;
	char 	*stop;
	int 	i;
	int 	*pipe_fds;
	
	if (command->command_parts[part + 1])
	{	
		stop = command->command_parts[part + 1];
		//printf("stop word: %s\n", stop);
		//set_new_pipe(command);
		pipe_fds = g_data->pipe_array[command->command_number];
		while (TRUE)
		{
			str = readline("> ");
			if (!str || ft_strcmp(str, stop))
			{	
				//write(pipe_fds[1], "\0", 1);
				close(pipe_fds[1]);
				break;
			}
			else
			{
				i = 0;
				write(pipe_fds[1], str, ft_strlen(str));
				write(pipe_fds[1], "\n",  1);
			}
		}
		rewrite_command_part_arr(command, part);
		i = 0;
		while (command->command_parts[i])
		{
			printf("parts: %s\n", command->command_parts[i]);
			fflush(stdout);
		}
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
			//printf("IN\n");
			//fflush(stdout);
			redirect_input(command, part);
			part = 0;
		}
		/*else if (ft_strcmp(command->command_parts[part], "<<"))
		{
			heredoc_r(command, part);
			//printf("sssss\n");
			//fflush(stdout);
			part = 0;
		}*/
		else 
			part++;
	}
}