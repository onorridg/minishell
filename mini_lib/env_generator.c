/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:18:13 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/25 13:42:17 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*variable_value_join(char *variable, char *value)
{
	char	*env_string;
	
	env_string = ft_strjoin(variable, "=");
	return (ft_strjoin(env_string, value));
}

static int	env_counter(void)
{
	t_envp	*node;
	int		count;

	node = g_data->first_envp;
	count = 0;
	while (node)
	{
		node = node->next;
		count++;
	}
	return (count);
}

char **env_generator(void)
{
	t_envp	*node;
	char	**env_arr;
	int		i;
	
	env_arr = (char **)malloc(sizeof(char *) * (env_counter()));
	if (!env_arr)
		exit(1);
	node = g_data->first_envp;
	i = 0;
	while (node)
	{
		env_arr[i++] = variable_value_join(node->variable, node->value);
		node = node->next;
	}
	i = 0;
	//while(env_arr[i])
	//	printf("%s\n", env_arr[i++]);
	return (env_arr);
}