/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:46:54 by mourhouc          #+#    #+#             */
/*   Updated: 2024/11/26 10:24:21 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *counter)
{
	char	digit;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*counter) += 11;
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		(*counter)++;
		n = -n;
		ft_putnbr(n, counter);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10, counter);
		ft_putnbr(n % 10, counter);
	}
	else
	{
		digit = n + 48;
		write(1, &digit, 1);
		(*counter)++;
	}
}
