/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:13:18 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/13 19:14:37 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*free_heredoc(t_heredoc *node)
{	t_heredoc *save;

	while (node)
	{	
		printf("%s\n", node->string);
		if (node->next)
			save = node->next;
		else
			break;
		free(node->string);
		free(node);
		node = save;
	}
	return (NULL);
}

t_heredoc	*heredoc(char *stop)
{	
	t_heredoc	*first;
	t_heredoc	*node;
	t_heredoc	*save;
	char		*str;
	
	str = readline("heredoc> ");
	if (ft_strcmp(str, stop))
			return (0);
	node = (t_heredoc *)malloc(sizeof(t_heredoc));
	node->string = str;
	node->next = NULL;
	first = node;
	while (TRUE)
	{
		str = readline("heredoc> ");
		if (ft_strcmp(str, stop))
			break;
		save = node;
		node = (t_heredoc *)malloc(sizeof(t_heredoc));
		save->next = node;
		node->string = str;
	}
	node->next = NULL;
	/*node = first;
	while (TRUE)
	{
		printf("%s\n", node->string);
		if (!node->next)
			break;
		node = node->next;
	}*/
	return (first);
}