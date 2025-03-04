/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:15:57 by mourhouc          #+#    #+#             */
/*   Updated: 2024/11/26 20:43:46 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthexa(int n, int *counter, int lower)
{
	unsigned int	num;
	char			*hexa;

	num = (unsigned int)n;
	if (lower == 1)
		hexa = "0123456789abcdef";
	else
		hexa = "0123456789ABCDEF";
	if (num >= 16)
	{
		ft_puthexa (num / 16, counter, lower);
		ft_puthexa (num % 16, counter, lower);
	}
	else
	{
		write (1, &hexa[num], 1);
		(*counter)++;
	}
}
