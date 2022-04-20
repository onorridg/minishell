/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:11:29 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/20 18:49:40 by onorridg         ###   ########.fr       */
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
	char flag;
	
    i = 0;
	flag = 0;
    while (string[i] && (string[i] != ch || flag != 0))
	{	
		if (string[i] == flag)
			flag = 0;
		else if (string[i] == '"' || string[i] == '\'')
			flag = string[i];
        i++;
	}
    return (i);
}

static int get_words(char **words, int count, char *string, char ch)
{
    int     word_len;
    int     i;
    int     j;
	int		k;
	char	flag;

    i = 0;
	k = 0;
    while (i < count)
    {   
        j = 0;
		flag = 0;
		while (*&string[k] == ch)
			k++;
        word_len = get_word_len(&string[k], ch);
        words[i] = (char *)malloc(sizeof(char) * (word_len + 1));
        if (!words[i])
            return(split_free(words, i - 1));
        while(*&string[k] && (*&string[k] != ch || flag != 0))
		{	
			if (*&string[k] == flag)
				flag = 0;
			else if (*&string[k] == '"' || *&string[k] == '\'')
				flag = *&string[k];
            words[i][j++] = *&string[k++];
		}
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
	char flag;

    i = 0;
    count = 0;
    flag = 0;
    while (string[i])
    {	
		while (string[i] && string[i] == ch)
			i++;
		if (string[i])
			count += 1;
		while(string[i] && (string[i] != ch || flag != 0))
		{	
			if (string[i] == flag)
				flag = 0;
			else if (string[i] == '"' || string[i] == '\'')
				flag = string[i];
			i++;
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
	count = 0;
    count = get_count(string, ch);
	if (count == 0)
		count = 1;  	// when press enter, mb need fix
	//printf("count: %i\n", count);
    words = malloc(sizeof(char *) * (count + 1));
    if (!words)
        return (0);
    if(get_words(words, count, string, ch))
        return (0);
    return (words);
}

/*int main(void)
{	
	char **result = ft_split("\" kek lol | 24 | aaaa              \" lol jekek |\"", ' ');
	int i = 0;
	while(result[i])
		printf("%s\n", result[i++]);
	return (0);
}*/
// " kek lol | 24 | aaaa"              " lol jekek | "
