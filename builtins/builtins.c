/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:12:06 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/21 19:03:08 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	plug(t_command *command)
{
	printf("[!] PLUG FUNCTION\n");
	return (0);
}

int ft_exit(t_command *command)
{	
	char *chr_number;
	int i;
	int number;
	int	sign;
	
	if (command->command_parts[2])
	{
		printf("exit: too many arguments\n"); //errno
		return (1);
	}
	if (command->command_parts[1])
	{	
		chr_number = command->command_parts[1];
		i = 0;
		sign = 1;
		if (chr_number[i] == '-')
		{
			sign = -1;
			i++;
		}	
		while(chr_number[i] >= '0' && chr_number[i] <= '9')
			number = number * 10 + (chr_number[i++] - '0');
		if (chr_number[i])
		{
			printf("numeric argument required\n"); //errno
			exit(1);
		}
		else
			exit(number * sign);
	}
	write(1, "exit\n", 5);
	exit(0);
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
	if (command->command_parts[1])
		chdir(command->command_parts[1]);
	else
		chdir(getenv("HOME"));
	return (0);
}