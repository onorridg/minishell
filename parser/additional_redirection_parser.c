/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_redirection_parser.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:35:22 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 16:35:24 by onorridg         ###   ########.fr       */
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

static	int redirection_string_len(char *string)
{
	int i;
	
	i = 0;
	if (string[i] == '<')
	{
		while(string[i] && string[i] == '<')
			i++;
	}
	else if (string[i] == '>')
	{
		while(string[i] && string[i] == '>')
			i++;
	}
	else
	{
		while (string[i] && string[i] != '>' && string[i] != '<')
			i++;
	}
	return (i);
}

static int split_redirection_len(char *string)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (string[i])
	{
		if ((string[i] == '<' && string[i + 1] == '<') || (string[i] == '>' && string[i + 1] == '>'))
		{
			count += 1;
			i++;
		}
		else if ((string[i] == '<') || (string[i] == '>'))
		{
			count += 1;
			i++;
		}
		else
		{
			while (string[i] && string[i] != '<' && string[i] != '>')
				i++;
			count += 1;
		}
	}
	return (count);
}

static char *set_redirection_string(char *string, int *start_p)
{
	int		start;
	char 	*new_string;
	int		len;
	int		i;

	start = *start_p;
	len = redirection_string_len(&string[start]);
	new_string = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_string)
		exit(1);
	i = 0;
	while (i < len)
	{
		new_string[i] = string[start + i];
		i++;
	}
	new_string[i] = '\0';
	*start_p = start + len; 
	return (new_string);
}

static void rewrite_command_parts(t_command *command, int part, char **new_parts, int new_parts_len)
{	
	int arr_l;
	char	**new_command_parts;
	int		i;
	int		j;
	int		k;

	arr_l = arr_len(command->command_parts) + new_parts_len;
	new_command_parts = (char **)malloc(sizeof(char *) * arr_l);
	if (!new_command_parts)
		exit(1);
	k = 0;
	while (i < part)
	{
		new_command_parts[i] = command->command_parts[k];
		i++;
		k++;
	}
	j = 0;
	while (new_parts[j])
	{
		new_command_parts[i] = new_parts[j];
		i++;
		j++;
	}
	k += 1;
	while(command->command_parts[k])
	{
		new_command_parts[i] = command->command_parts[k];
		i++;
		k++;
	}
	new_command_parts[i] = 0;
	command->command_parts = new_command_parts;
}

static void split_redirection(t_command *command, int part)
{
	int 	len;
	char 	**new_command_parts;
	int		i;
	int		start;

	len = split_redirection_len(command->command_parts[part]);
	//printf("count: %i\n", len);
	new_command_parts = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_command_parts)
		exit(1);
	i = 0;
	start = 0;
	while (i < len)
	{	
		//printf("start: %s\n", &command->command_parts[part][start]);
		new_command_parts[i] = set_redirection_string(command->command_parts[part], &start);
		i++;
	}
	new_command_parts[i] = 0;
	i = 0;
	//printf("\n");
	//while (new_command_parts[i])
	//	printf("%s\n", new_command_parts[i++]);
	//printf("\n");
	rewrite_command_parts(command, part, new_command_parts, len);
}

int check_redirection_sign(char *string)
{
	char chr1;
	char chr2;
	
	chr1 = ft_find_char_in_string(string, '<');
	chr2 = ft_find_char_in_string(string, '>');
	if (chr1 != -1 && (ft_strcmp(string, "<") == 0 && ft_strcmp(string, "<<") == 0))
		return (1);
	if (chr2 != -1 && (ft_strcmp(string, ">") == 0 && ft_strcmp(string, ">>") == 0))
		return (1);
	return (0);
}

void additional_redirection_parser(t_command *command)
{
	int 	i;
	int		chr1;
	int		chr2;
	char	sign;
	i = 0;
	chr1 = -1;
	chr2 = -1;
	while (command->command_parts[i])
	{
		if (check_redirection_sign(command->command_parts[i]))
		{
 			split_redirection(command, i);
			i = 0;
		}
		else 
			i++;
	}
	i = 0;
	//while (command->command_parts[i])
	//	printf("|%s|\n", command->command_parts[i++]);
	//exit(0);
}
// a0 >a1>>a2<<a3<a4 a5 