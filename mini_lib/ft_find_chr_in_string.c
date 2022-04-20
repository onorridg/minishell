/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_chr_in_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:54:14 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/19 17:56:34 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	find_char_in_string(char *string, char ch)
{
	int i;

	i = 0;
	while (string[i])
	{
		if (string[i] == ch)
			return (i);
		i++;
	}
	return (-1);
}