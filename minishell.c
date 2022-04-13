/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:33:20 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/12 19:21:34 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int bash(void)
{
	return 0;
}

static int minishell(int com_num, char **words)
{	
	t_command *com;
	BUILTIN **builtins_arr;
	
	com = (t_command *)malloc(sizeof(t_command));
	builtins_arr = set_ptr_func_to_arr();
	if (com_num == 0)
	{	
		com->option = 1;
		if (words[1] && ft_strcmp(words[1], "-n"))
			com->option = 0;
	}
	com->data = words;
	builtins_arr[com_num](com);
	free(com);
	return 0;
}

int main(int ac, char **av)
{	
	char **words;
	char *str;
	int command_number;
	int exit;

	exit = 1;
	while (exit)
    {
        str = readline("minishell$ ");
		words = ft_split(str, ' ');
		command_number = builtin_chek(words[0]);
		if (command_number == 6)
			exit = 0;
		else if (command_number != -1)
			minishell(command_number, words);
		else
			bash();
        free(str);
		//split_free(words, -1); // does not work
    }
}
