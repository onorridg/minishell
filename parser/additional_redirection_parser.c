/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_redirection_parser.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:35:22 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/11 19:24:53 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int arr_len(char **command_parts)
{
	int i;

	i = 0;
	while (command_parts[i])
		i++;
	return (i);
}

static void split_redirections(t_command *command, int part, char *redirection)
{	
	int 	arr_l;
	char	**new_command_parts;
	int		i;
	int		j;
	char	*file_name;
	char	*redirection_sign;
	
	redirection_sign = ft_set_mem_aloc(redirection);
	//printf("redirection_sign: %s\n", redirection_sign);
	file_name = ft_set_mem_aloc(&command->command_parts[part][ft_strlen(redirection)]);
	//printf("file_name: %s\n", file_name);
	arr_l = arr_len(command->command_parts) + 1;
	new_command_parts = (char **)malloc(sizeof(char *) * (arr_l + 2));
	if (!new_command_parts)
		exit(1);
	free(command->command_parts[i]);
	i = 0;
	j = 0;
	while (i < part)
	{	
		printf("%s\n", command->command_parts[j]);
		new_command_parts[i] = command->command_parts[j];
		i++;
		j++;
	}
	printf("\n");
	new_command_parts[i] = redirection_sign;
	i++;
	new_command_parts[i] = file_name;
	i++;
	j++;
	while (command->command_parts[j])
	{
		new_command_parts[i] = command->command_parts[j];
		i++;
		j++;
	}
	new_command_parts[i] = 0;
	//free(command->command_parts);
	command->command_parts = new_command_parts;
}

void additional_redirection_parser(t_command *command)
{
	int i;
	int signs;
		
	i = 0;
	signs = 1;
	while (command->command_parts[i])
	{	
		//printf("%s\n", command->command_parts[i]);
		if (command->command_parts[i][0] == '<')
		{
			if (command->command_parts[i][1] == '<' && command->command_parts[i][2])
			{
				split_redirections(command, i, "<<");
				i = 0;
			}
			else if (command->command_parts[i][1])
			{
				split_redirections(command, i, "<");
				i = 0;
			}
			else
				i++;
		}
		else if (command->command_parts[i][0] == '>')
		{	
			if (command->command_parts[i][1] == '>' && command->command_parts[i][2])
			{
				split_redirections(command, i, ">>");
				i = 0;
			}
			else if (command->command_parts[i][1])
			{
				split_redirections(command, i, ">");
				i = 0;
			}
			else
				i++;
			signs = 1;	
		}
		else
			i++;
	}
	i = 0;
	while (command->command_parts[i])
		printf("|%s| ", command->command_parts[i++]);
	printf("\n");
	exit(0);
}