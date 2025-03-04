/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:16:59 by mourhouc          #+#    #+#             */
/*   Updated: 2024/11/23 16:40:28 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putaddr(void *ptr, int *counter)
{
	unsigned long	addr;
	char		*hexa;

	hexa = "0123456789abcdef";
	addr = (unsigned long)ptr;
	if (addr >= 16)
	{
		ft_putaddr((void *)(addr / 16), counter);
		ft_putaddr((void *)(addr % 16), counter);
	}
	else
	{
		write(1, &hexa[addr], 1);
		(*counter)++;
	}
}
