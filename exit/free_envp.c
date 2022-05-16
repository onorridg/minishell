/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:29:19 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 15:46:23 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_own_envp(void)
{
	t_own_var	*node;
	t_own_var	*clear_data;

	node = g_data->first_var;
	while (node)
	{
		clear_data = node;
		node = node->next;
		if (clear_data->value)
			free(clear_data->value);
		if (clear_data->variable)
			free(clear_data->variable);
		free(clear_data);
	}
}

static void	free_envp(void)
{
	t_envp	*node;
	t_envp	*clear_data;

	node = g_data->first_envp;
	while (node)
	{
		clear_data = node;
		node = node->next;
		if (clear_data->value)
			free(clear_data->value);
		if (clear_data->variable)
			free(clear_data->variable);
		free(clear_data);
	}
}

void	free_all_envp(void)
{
	free_envp();
	free_own_envp();
	free(g_data);
}
