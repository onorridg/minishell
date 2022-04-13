/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:12:06 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/12 18:44:39 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_command *com)
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

int ft_cd(t_command *com)
{	
	/* "cd " cd с пробелом не работает */
	if (com->data[1])
		chdir(com->data[1]);
	else
		chdir(getenv("HOME"));
	return (0);
}

int	ft_echo(t_command *com)
{
	int	i;
	int j;

	j = 1;
	if (com->option == 0)
		j = 2;
	while (com->data[j])
	{
		i = 0;
		while (com->data[j][i])
			write(1, &com->data[j][i++], 1);
		j++;
		if (com->data[j])
			write(1, " ", 1);	
	}
	if (com->option)
			write(1, "\n", 1);
	return (0);
}