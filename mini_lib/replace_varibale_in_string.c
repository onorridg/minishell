/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_varibale_in_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:22 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/26 18:49:15 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_left_string_part(char *string)
{
	int 	i;
	char	*left_part;

	i = 0;
	left_part = (char *)malloc(sizeof(char) * (ft_find_char_in_string(string, '$') + 1));
	if (!left_part)
		exit(1);
	while(string[i] && string[i] != '$')
	{
		left_part[i] = string[i];
		i++;
	}
	left_part[i] = '\0';
	return (left_part);
}

char *get_right_string_part(char *string)
{
	int 	i;
	int		j;
	int 	string_len;
	char	*right_part;
	
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
	char	*left_part;
	char	*right_part;
	char	*value;

	i = 0;
	if (string[i] != '\'')
	{
		while (string[i])
		{
			if (string[i] == '$')
			{
				i += 1;
				value = value_to_string(&string[i]);
				left_part = get_left_string_part(string);
				right_part = get_right_string_part(&string[i]);
				if (value)
				{
					string = ft_strjoin(left_part, value);
					string = ft_strjoin(string, right_part);
				}
				else
				{
					string = ft_strjoin(left_part, " ");
					string = ft_strjoin(string, right_part);
				}
				//free(left_part);
				//free(value);
				//free(right_part);
				i = 0;
			}
			else
				i++;
		}
	}
	//printf("string: |%s|\n", string);
	//fflush(stdout);
	return (string);
}

/*int main(void)
{
	//inser_value_to_string("one $USER two three $TEST");
	inser_value_to_string("1$USER    2$USER    3$USER lol");
}*/