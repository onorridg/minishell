/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:11:29 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/19 14:01:29 by onorridg         ###   ########.fr       */
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
	int		k;

    i = 0;
	k = 0;
    while (i < count)
    {   
        j = 0;
		while (*&string[k] == ch)
			k++;
        word_len = get_word_len(&string[k], ch);
        words[i] = (char *)malloc(sizeof(char) * (word_len + 1));
        if (!words[i])
            return(split_free(words, i - 1));
        while(*&string[k] && *&string[k] != ch)
            words[i][j++] = *&string[k++];
        //if (*string)
        //    string++;
        words[i][j] = '\0';
		//printf()
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
		while (string[i++] == ch)
		{
        	if (string[i + 1] && string[i + 1] != ch)
            	count += 1;
		}
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
