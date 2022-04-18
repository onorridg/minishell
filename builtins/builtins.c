/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:12:06 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/18 18:14:56 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_data *data)
{
	int i;
	int j;
	

	i = 0;
	while (data->envp[i])
	{	
		write(1, data->envp[i], ft_strlen(data->envp[i]));
		write(1, "\n", 1);
		i++;
	}
	printf("%i\n", i);
	return (0);
}

int ft_pwd(t_data *data)
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

int ft_cd(t_data *data)
{	
	/* "cd " cd с пробелом не работает */
	if (data->command)
		chdir(data->command);
	else
		chdir(getenv("HOME"));
	return (0);
}

int	ft_echo(t_data *data)
{
	/*int	i;
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
			write(1, "\n", 1);*/
	return (0);
}