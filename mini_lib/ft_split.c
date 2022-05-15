/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:11:29 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/15 14:07:16 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_free(char **words, int count)
{
	int	i;

	i = 0;
	if (count != -1)
	{
		while (i < count)
		{	
			if (words && words[i])
				free(words[i]);
			i++;
		}
	}
	else
	{
		while (words && words[i])
		{	
			free(words[i]);
			i++;
		}
		
	}
	free(words);
	return (0);
}

static int	get_word_len(char *string, char ch)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while (string[i] && (string[i] != ch || flag != 0))
	{
		if (string[i] == '"' || string[i] == '\'')
		{
			if (flag == 0)
				flag = string[i];
			else if (string[i] == flag)
				flag = 0;
		}
		i++;
	}
	return (i);
}

static int	get_words(char **words, int count, char *string, char ch)
{
	t_split	data;

	data.i = 0;
	data.k = 0;
	while (data.i < count)
	{
		data.j = 0;
		data.flag = 0;
		while (string[data.k] == ch)
			data.k++;
		data.word_len = get_word_len(&string[data.k], ch);
		words[data.i] = (char *)malloc(sizeof(char) * (data.word_len + 1));
		if (!words[data.i])
			return (split_free(words, data.i - 1));
		while (string[data.k] && (string[data.k] != ch || data.flag != 0))
		{
			is_quote(&data, string);
			words[data.i][data.j++] = string[data.k++];
		}
		words[data.i][data.j] = '\0';
		data.i++;
	}
	words[data.i] = 0;
	return (0);
}

static int	get_count(char *string, char ch, int count, int i)
{
	char	flag;

	flag = 0;
	while (string[i])
	{
		while (string[i] && string[i] == ch)
			i++;
		if (string[i] || ch == '|')
			count += 1;
		while (string[i] && (string[i] != ch || flag != 0))
		{	
			if (string[i] == '"' || string[i] == '\'')
			{
				if (flag == 0)
					flag = string[i];
				else if (string[i] == flag)
					flag = 0;
			}
			i++;
		}
	}
	return (count);
}

char	**ft_split(char *s, char ch)
{
	int		count;
	char	**words;
	char	*string;

	string = s;
	count = 0;
	count = get_count(string, ch, 0, 0);
	if (count == 0 && ft_strlen(string) > 0)
		count = 1;
	if (count == 0)
		return (0);
	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (0);
	if (get_words(words, count, string, ch))
		return (0);
	return (words);
}
