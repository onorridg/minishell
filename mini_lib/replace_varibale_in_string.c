/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_varibale_in_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:22 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/10 14:10:53 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			//printf("quote[%i] = %c\n", i, quote);
			i++;
		}
		else if (string[i] == '$' && (quote == 0 || quote == '"'))
		{
			i += 1;
			value = value_to_string(&string[i]);
			//printf("value: |%s|\n", value);
			left_part = get_left_string_part(string, i - 1);
			//printf("left_part: |%s|\n", left_part);
			right_part = get_right_string_part(&string[i]);
			//printf("rifht_part|%s|\n", right_part);
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
			//printf("string: |%s|\n\n", string);
			free(left_part);
			free(value);
			free(right_part);
			quote = 0;
			i = 0;
		}
		else
			i++;
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