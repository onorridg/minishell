/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:42:26 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/22 18:16:22 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		path_command(t_command *command)
{	char *path;

	if (ft_strlen(command->command_parts[0]) > 0)
	{
		path = get_command_path(command);
		if (path)
			printf("%s\n", path);
	}
	//else
	//	print("error pipe\n")
	//printf("TEST bash\n");
	return 0;
}