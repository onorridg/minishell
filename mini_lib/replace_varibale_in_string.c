/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_varibale_in_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:22 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/26 15:22:03 by onorridg         ###   ########.fr       */
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
	//printf("left: %s\n", left_part);
	return (left_part);
}

char *get_right_string_part(char *string)
{
	int 	i;
	int		j;
	int 	string_len;
	char	*right_part;
	i = ft_char_len(string, TRUE);
	//printf("rigt string : |%s|\n", &string[i]);
	string_len = ft_strlen(&string[i]);
	//printf("string len %i | i = %i\n", string_len, i);
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
	right_part[i] = '\0';
	//printf("\nrigt: %i |%s|\n",i, right_part);
	return (right_part);
}

char *inser_value_to_string(char *string)
{
	int 	i;
	char	*new_string;
	char	*left_part;
	char	*right_part;
	//char	value[] = "|value|";
	char	*value;

	i = 0;
	while (string[i])
	{	
		//printf("%c\n",string[i]);
		if (string[i] == '$')
		{
			i += 1;
			value = value_to_variable(&string[i]);
			printf("value: %s\n", value);
			fflush(stdout);
			left_part = get_left_string_part(string);
			right_part = get_right_string_part(&string[i]);
			string = ft_strjoin(left_part, value);
			string = ft_strjoin(string, right_part);
			//free(left_part);
			//free(value);
			//free(right_part);
			i = 0;
			//printf("result: %s\n", string);
		}
		else
			i++;
	}
	//printf("\nfinal result: %s\n", string);
	return (string);
}

/*int main(void)
{
	//inser_value_to_string("one $USER two three $TEST");
	inser_value_to_string("1$USER 2$USER 3$USER");
}*/