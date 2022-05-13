/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:44:59 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 18:02:46 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_command *command)
{	
	int		i;
	char	*dir;
	int		*pipes;

	pipes = is_redirection(command);
	dir = my_getenv("PWD");
	if (!dir)
		error_handler(command);
	i = 0;
	while (dir[i])
		write(pipes[1], &dir[i++], 1);
	write(pipes[1], "\n", 1);
	close(pipes[1]);
	set_exit_code(0);
	return (0);
}
