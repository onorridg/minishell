/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:12:54 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/06 17:06:19 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_command_path(t_command *command)
{
	char	**arr_paths;
	int 	i;
	char	*path;
	
	path = my_getenv("PATH");
	if (!path)
	{
		errno = ENOENT;
		error_handler(command);
		return (0);
	}
	arr_paths = ft_split(path, ':');
	if (!arr_paths)
		return (0);
	i = 0;
	while(arr_paths[i])
	{	
		path = ft_strjoin_path(arr_paths[i], command->command_parts[0]);
		if (!access(path, 1))
		{
			split_free(arr_paths, -1);
			return (path);
		}
		free(path);
		i++;
	}
	split_free(arr_paths, -1);
	return (0);
}