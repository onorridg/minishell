/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alphabet_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:42:25 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 17:52:13 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	need_swap(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

static void	sort(char **envp)
{
	int		i;
	char	*swap;

	i = 0;
	while (envp[i])
	{
		if (envp[i + 1] && need_swap(envp[i], envp[i + 1]) > 0)
		{
			swap = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = swap;
		}
		i++;
	}
}

char	**alphabet_sort(void)
{
	char	**envp_array;
	int		i;

	envp_array = env_generator();
	i = 0;
	i = 0;
	while (envp_array[i])
	{	
		sort(envp_array);
		i++;
	}
	return (envp_array);
}
