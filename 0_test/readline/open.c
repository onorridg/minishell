/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:23:33 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/27 15:27:17 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int main(void)
{	int fd;
	int buf[1];
	
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{	
		printf("[!] ERROR\n");
	}
	else 
	{
		while (read(fd, buf, 1) > 0)
		{
			printf("char - |%c|\n", buf[0]);
			//write(pipe_fds[1], buf, 1);
			buf[0] = 0;
		}
		printf("---------------------------------\n");
		close(fd);
	}
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{	
		printf("[!] ERROR\n");
	}
	else 
	{
		while (read(fd, buf, 1) > 0)
		{
			printf("char - |%c|\n", buf[0]);
			//write(pipe_fds[1], buf, 1);
			buf[0] = 0;
		}
		printf("---------------------------------\n");
		close(fd);
	}
}