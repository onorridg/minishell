/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:46:11 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/03 11:24:28 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    display_exit_code(int exit_code)
{   
	char	num;

	if (exit_code < 0)
	{
		exit_code *= -1;
		write(1, "-", 1);
	}
	if (exit_code % 10 != 0 )
	{
		display_exit_code(exit_code / 10);
		num = (exit_code % 10) + '0';
		fprintf(stderr, "IN\n");
		fflush(stderr);
		write(1, &num, 1);
	}		
}

/*int main(void)
{
	display_exit_code(-22346);
}*/