/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:11:53 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/22 13:47:53 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l_s1;
	size_t	l_s2;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (l_s1 + l_s2) + 1);
	if (!new)
		exit(1);
	if (l_s1 == 0 && l_s2 == 0)
		*new = '\0';
	else if (new)
	{
		if (l_s1 != 0)
			ft_strlcpy(new, (char *) s1, l_s1 + 1);
		if (l_s2 != 0)
			ft_strlcpy(&new[l_s1], (char *)s2, l_s2 + 1);
	}
	return (new);
}
