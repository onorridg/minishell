/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_varibale_in_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:22 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/15 11:03:15 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_left_string_part(char *string, int stop)
{
	int		i;
	char	*left_part;

	i = 0;
	left_part = (char *)malloc(sizeof(char) * (stop + 1));
	if (!left_part)
		exit(1);
	while (string[i] && i < stop)
	{
		left_part[i] = string[i];
		i++;
	}
	left_part[i] = '\0';
	return (left_part);
}

char	*get_right_string_part(char *string, char *full_string)
{
	int		i;
	int		j;
	int		string_len;
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

char	*parse_variable(char *string)
{
	char	*variable;

	variable = ft_copy_str_len(string, ft_char_len(string, TRUE));
	//free(string);
	return (variable);
}

char	*value_to_string(char *string)
{
	char	*value;
	t_envp	*var;

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

char	*inser_value_to_string(char *str, int i, char quote, char *val)
{
	char	*l_part;
	char	*r_part;
	char	*n_string;

	while (str[i])
	{
		if (set_qoute_replace_variable(&quote, str, i))
			i++;
		else if (str[i] == '$' && (quote == 0 || quote == '"'))
		{
			i += 1;
			val = value_to_string(&str[i]);
			l_part = get_left_string_part(str, i - 1);
			r_part = get_right_string_part(&str[i], str);
			free(str);
			n_string = ft_strjoin(l_part, val);
			str = ft_strjoin(n_string, r_part);
			free_replace_variable(n_string, l_part, val, r_part);
			quote = 0;
			i = 0;
		}
		else
			i++;
	}
	return (str);
}
