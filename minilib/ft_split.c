/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:11:29 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/16 14:20:54 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int split_free(char **words, int count)
{
    int i;

    i = 0;
	if (count != -1)
	{
		while (i < count)
			free(words[i++]);
	}
	else 
	{
		while (words[i])
			free(words[i++]);
	}
    free(words);
    return (0);
}

static int get_word_len(char *string, char ch)
{
    int i;

    i = 0;
    while (string[i] && string[i] != ch)
        i++;
    return (i);
}

static int get_words(char **words, int count, char *string, char ch)
{
    int     word_len;
    int     i;
    int     j;

    i = 0;
    while (i < count)
    {   
        j = 0;
        word_len = get_word_len(string, ch);
        words[i] = (char *)malloc(sizeof(char) * (word_len + 1));
        if (!words[i])
            return(split_free(words, i - 1));
        while(*string && *string != ch)
            words[i][j++] = *string++;
        if (*string)
            string++;
        words[i][j] = '\0';
        i++;
    }
    words[i] = 0;
    return (0);
}

static int get_count(char *string, char ch)
{
    int count;
    int i;

    i = 0;
    count = 0;
    
    while (string[i])
    {
        if (string[i++] == ch)
            count += 1;
    }
    return (count);
}

char **ft_split(char *s, char ch)
{
    int     count;
    char    **words;
    char    *string;

    string = s;
    count = get_count(string, ch) + 1;
    //if (ch == ':')
    //    count += 1;
    words = malloc(sizeof(char *) * (count + 1));
    if (!words)
        return (0);
    if(get_words(words, count, string, ch))
        return (0);
    return (words);
}
