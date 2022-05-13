/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:12:54 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 21:16:03 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_command_path(t_command *command)
{
	char	**arr_paths;
	int		i;
	char	*path;

	path = my_getenv("PATH");
	if (!path)
		return (0);
	arr_paths = ft_split(path, ':');
	if (!arr_paths)
		return (0);
	i = 0;
	while (arr_paths[i])
	{	
		path = ft_strjoin_path(arr_paths[i], command->command_parts[0]);
		if (!access(path, X_OK))
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
