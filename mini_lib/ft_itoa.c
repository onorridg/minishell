/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:29:16 by                   #+#    #+#             */
/*   Updated: 2022/05/03 12:26:34 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_write_arr(char *arr, int len, char sign, int n)
{
	int		i;

	i = len;
	arr[i] = '\0';
	i--;
	if (n == 0)
		arr[i] = '0';
	else
	{
		while (n > 0)
		{
			arr[i--] = (n % 10) + '0';
			n /= 10;
		}
		if (sign == '-')
			arr[i] = '-';
	}
}

static int	ft_int_len(int n)
{
	int		i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	sign;
	char	*arr;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = '+';
	if (n < 0)
	{
		sign = '-';
		n *= -1;
	}
	len = ft_int_len(n);
	if (sign == '-')
		len += 1;
	arr = (char *)malloc(sizeof(char) * len + 1);
	if (arr)
		ft_write_arr(arr, len, sign, n);
	return (arr);
}
