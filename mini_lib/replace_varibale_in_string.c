/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_varibale_in_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:22 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 13:37:15 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static char	**split_value(char *value)
{
	char	**values;
	
	values = ft_split(value, ' ');
	if (!value)
		exit(1);
	if (value[1])
		return (value);
	return (0);
}*/

char *get_left_string_part(char *string, int stop)
{
	int 	i;
	char	*left_part;

	i = 0;
	left_part = (char *)malloc(sizeof(char) * (stop + 1));
	if (!left_part)
		exit(1);
	while(string[i] && i < stop)
	{
		left_part[i] = string[i];
		i++;
	}
	left_part[i] = '\0';
	return (left_part);
}

char *get_right_string_part(char *string, char *full_string)
{
	int 	i;
	int		j;
	int 	string_len;
	char	*right_part;
	
	if (ft_strcmp(full_string, "$?"))
		i = 1;
	else 
		i = ft_char_len(string, TRUE);
	string_len = ft_strlen(&string[i]);
	right_part = (char *)malloc(sizeof(char) * (string_len + 1));
	if (!right_part)
		exit(1);
	j = 0;
	while (string[i])
	{
		right_part[j] = string[i];
		i++;
		j++;
	}
	right_part[j] = '\0';
	return (right_part);
}

char *parse_variable(char *string)
{
	char *variable;

	variable = ft_copy_str_len(string, ft_char_len(string, TRUE));
	return (variable);
}

char	*value_to_string(char *string)
{
	char 		*value;
	t_envp		*var;

	if (!ft_strcmp(string, "?"))
		string = parse_variable(string);
	value = NULL;
	var = g_data->first_envp;
	value = my_getenv(string);
	if (!value)
		value = get_own_env(string);
	if (!value)
		value = ft_set_mem_aloc("");
	return (value);
}

char *inser_value_to_string(char *string)
{
	int 	i;
	char	quote;
	char	*left_part;
	char	*right_part;
	char	*value;
	char	*new_string;

	i = 0;
	quote = 0;
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '"')
		{
			if (quote == 0)
				quote = string[i];
			else if (quote == string[i])
				quote = 0;
			i++;
		}
		else if (string[i] == '$' && (quote == 0 || quote == '"'))
		{
			i += 1;
			value = value_to_string(&string[i]);
			left_part = get_left_string_part(string, i - 1);
			right_part = get_right_string_part(&string[i], string);
			free(string);
			if (value)
			{
				new_string = ft_strjoin(left_part, value);
				string = ft_strjoin(new_string, right_part);
				free(new_string);
			}
			else
			{
				new_string = ft_strjoin(left_part, " ");
				string = ft_strjoin(new_string, right_part);
				free(new_string);
			}
			free(left_part);
			free(value);
			free(right_part);
			quote = 0;
			i = 0;
		}
		else
			i++;
	}
	return (string);
}
