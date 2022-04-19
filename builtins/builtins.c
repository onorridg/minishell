/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:12:06 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/19 14:27:05 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int plug(t_command *command)
{
	printf("[!] PLUG FUNCTION\n");
	return 0;
}

int ft_env(t_command *command)
{
	int i;
	int j;
	

	i = 0;
	while (command->envp[i])
	{	
		write(1, command->envp[i], ft_strlen(command->envp[i]));
		write(1, "\n", 1);
		i++;
	}
	//printf("%i\n", i);
	return (0);
}

int ft_pwd(t_command *command)
{	
	int		i;
	char	dir[DIR_MAX];
	
	getcwd(dir, DIR_MAX);
	i = 0;

	while (dir[i])
		write(1, &dir[i++], 1);
	write(1, "\n", 1);
	return 0;
}

int ft_cd(t_command *command)
{	
	/* "cd " cd с пробелом не работает */
	if (command->command_parts[1])
		chdir(command->command_parts[1]);
	else
		chdir(getenv("HOME"));
	return (0);
}

int	ft_echo(t_command *command)
{
	int	i;
	int j;
	int newline;
	
	j = 1;
	newline = TRUE;
	/*if (ft_strcmp(command->command_parts[1], "-n"))
	{
		j = 2;
		newline = FALSE;
	}*/
	//printf("j = %i\n", j);
	j = 0;
	while (command->command_parts[j])
	{
		i = 0;
		while (command->command_parts[j][i])
			write(1, &command->command_parts[j][i++], 1);
		j++;
		if (command->command_parts[j])
			write(1, " ", 1);	
	}
	//if (newline)
	write(1, "\n", 1);
	return (0);
}