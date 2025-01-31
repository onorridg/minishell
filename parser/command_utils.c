/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:24:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 15:58:24 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_chek(char *builtin)
{	
	if (!builtin)
		return (-1);
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
	else
		return (7);
}

t_BUILTIN	**set_ptr_func_to_arr(void)
{
	t_BUILTIN	**builtins_arr;

	builtins_arr = (t_BUILTIN **)malloc(sizeof(t_BUILTIN *) * 9);
	if (!builtins_arr)
		exit(1);
	builtins_arr[0] = ft_echo;
	builtins_arr[1] = ft_cd;
	builtins_arr[2] = ft_pwd;
	builtins_arr[3] = ft_export;
	builtins_arr[4] = ft_unset;
	builtins_arr[5] = ft_env;
	builtins_arr[6] = ft_exit;
	builtins_arr[7] = path_command;
	builtins_arr[8] = 0;
	return (builtins_arr);
}
