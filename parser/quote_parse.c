/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:14:06 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/10 15:33:59 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *quote_parse(char *string)
{
    int     i;
    int     j;
    char    quote;
    int     start;
    int     finish;
    char    *new_string;

    quote = 0;
    i = 0;
    j = 0;
    //printf("string[%i]: %s\n", ft_strlen(string), string);
    new_string = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
    if (!new_string)
        exit(1);
    while (string[i])
    {
        if (string[i] == '\'' || string[i] == '"')
        {   
            //printf("if\n");
            if (quote == 0)
                quote = string[i];
            else if (quote == string[i])
                quote = 0;
            else
            {
                new_string[j] = string[i];
                j++;
            }
        }
        else
        {
            new_string[j] = string[i];
            j++;
        }
        i++;
    }
    new_string[j] = '\0';
    free(string);
    //printf("new_string: %s\n", new_string);
    return (new_string);
    
}

/*int main(void)
{
    quote_parse("\"e'xp'o'r't'\"");
}*/