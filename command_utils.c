/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:24:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/13 16:30:33 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_chek(char *builtin)
{
	if (ft_strcmp(builtin, "echo"))
		return (0);
	else if (ft_strcmp(builtin, "cd"))
		return (1);
	else if (ft_strcmp(builtin, "pwd"))
		return (2);
	else if (ft_strcmp(builtin, "export"))
		return (3);
	else if (ft_strcmp(builtin, "unset"))
		return (4);
	else if (ft_strcmp(builtin, "env"))
		return (5);
	else if (ft_strcmp(builtin, "exit"))
		return (6);
	return (-1);
}

BUILTIN	**set_ptr_func_to_arr(void)
{
	BUILTIN **builtins_arr;
	
	builtins_arr = (BUILTIN **)malloc(sizeof(BUILTIN) * 4);
	if (!builtins_arr)
	{
		printf("FCK malloc !\n");
		return 0;
	}
	builtins_arr[0] = ft_echo;
	builtins_arr[1] = ft_cd;
	builtins_arr[2] = ft_pwd;
	builtins_arr[3] = 0;
	return builtins_arr;
}

char    *get_command_path(char *command)
{
	char	**arr_paths;
	int 	i;
	char	*path;
	
	arr_paths = ft_split(getenv("PATH"), ':');
	if (!arr_paths)
		return (0);
	i = 0;
	while(arr_paths[i])
	{	
		path = ft_strjoin(arr_paths[i], command);
		if (!access(path, 1))
			return (path);
		i++;
	}
	return (0);
}