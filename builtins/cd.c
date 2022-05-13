/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:46:25 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 17:51:11 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cd_exit(int result, t_command *command)
{
	char	dir[DIR_MAX];
	char	**pwd;

	if (result == -1)
	{	
		set_exit_code(1);
		error_handler(command);
	}
	else
		set_exit_code(0);
	getcwd(dir, DIR_MAX);
	pwd = (char **)malloc(sizeof(char *) * 3);
	pwd[0] = ft_set_mem_aloc("PWD");
	pwd[1] = ft_set_mem_aloc(dir);
	pwd[2] = 0;
	set_env_variable(pwd);
}

int	ft_cd(t_command *command)
{	
	int		result;
	char	*home_path;

	if (command->command_parts[1])
		result = chdir(command->command_parts[1]);
	else
	{
		home_path = my_getenv("HOME");
		if (!home_path)
			result = -1;
		else
		{
			result = chdir((const char *)home_path);
			free(home_path);
		}
	}
	cd_exit(result, command);
	return (0);
}
