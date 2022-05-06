/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:30:20 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/06 18:59:56 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void pipe_array(void)
{
	int	**pipe_array;
	int i;
	int *pipe_fd;
	
	pipe_array = (int **)malloc(sizeof(int *) * (g_data->command_counter + 1));
	if (!pipe_array)
		exit(1);
	i = 0;
	while (i < g_data->command_counter)
	{	
		pipe_fd = (int *)malloc(sizeof(int) * (2));
		if (!pipe_fd)
			exit(1);
		if (pipe(pipe_fd) == -1)
			exit(1);
		pipe_array[i++] = pipe_fd;
	}
	//printf("pipes: %i\n", i);
	pipe_array[i] = 0;
	g_data->pipe_array = pipe_array;
	/*i = 0;
	while(i < g_data->command_counter)
	{
		printf("%i: [%i]|[%i]\n", i, g_data->pipe_array[i][0], g_data->pipe_array[i][1]);
		i++;
	}*/
}

/*int main(void)
{	
	int count = 10;
	ft_pipe_array(count);
	int i = 0;
	while(i < count)
	{
		printf("%i: [%i]|[%i]\n", i, g_data->pipe_array[i][0], g_data->pipe_array[i][1]);
		i++;
	}
	return (0);
}*/