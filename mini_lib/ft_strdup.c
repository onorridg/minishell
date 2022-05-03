/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:31:51 by                   #+#    #+#             */
/*   Updated: 2022/05/03 12:27:21 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		str_len;

	str_len = ft_strlen((char *)s);
	new_str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (new_str)
	{
		ft_memcpy(new_str, s, str_len);
		new_str[str_len] = '\0';
	}
	return ((char *)new_str);
}
