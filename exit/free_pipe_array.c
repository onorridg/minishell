/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:58:30 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 18:41:38 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipe_array(void)
{
	int	i;

	i = 0;
	while (g_data->pipe_array[i])
	{
		close(g_data->pipe_array[i][0]);
		close(g_data->pipe_array[i][1]);
		free(g_data->pipe_array[i++]);
	}
	free(g_data->pipe_array);
}
