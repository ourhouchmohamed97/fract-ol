/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:46:25 by mourhouc          #+#    #+#             */
/*   Updated: 2024/11/29 20:13:23 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_conversion(va_list args, char *format, int *count)
{
	int	lower;

	lower = 0;
	if (*format == 'c')
		ft_putchar(va_arg(args, int), count);
	else if (*format == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (*format == 'p')
	{
		write(1, "0x", 2);
		(*count) += 2;
		ft_putaddr(va_arg(args, void *), count);
	}
	else if (*format == 'd' || *format == 'i')
		ft_putnbr(va_arg(args, int), count);
	else if (*format == 'u')
		ft_putnbr_unsigned(va_arg(args, unsigned int), count);
	else if (*format == 'x' || *format == 'X')
	{
		if (*format == 'x')
			lower = 1;
		ft_puthexa(va_arg(args, int), count, lower);
	}
	else if (*format == '%')
		ft_putchar('%', count);
}

t_flag	f1(char *format)
{
	t_flag	res;

	res.f1 = 0;
	res.f2 = 0;
	res.f3 = 0;
	while (*format)
	{
		if (*format == '#')
			res.f1 = 1;
		else if (*format == '+')
			res.f2 = 2;
		else if (*format == ' ')
			res.f3 = 3;
		format++;
	}
	return (res);
}

void	ft_flag(va_list args, char **format, int *count)
{
	va_list	cpy;
	int		num;
	t_flag	result;

	va_copy(cpy, args);
	num = va_arg(cpy, int);
	result = f1(*format);
	while (**format == '#' || **format == '+' || **format == ' ')
		(*format)++;
	if (**format == 'x' && result.f1 == 1 && num != 0)
		(*count) += write(1, "0x", 2);
	else if (**format == 'X' && result.f1 == 1 && num != 0)
		(*count) += write(1, "0X", 2);
	if ((**format == 'd' || **format == 'i') && (num >= 0))
	{
		if (result.f2 == 2)
			(*count) += write(1, "+", 1);
		else if (result.f3 == 3)
			(*count) += write(1, " ", 1);
	}
	va_end(cpy);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	va_start(args, format);
	count = 0;
	if (write(1, NULL, 0) == -1)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '#' || *format == '+' || *format == ' ')
				ft_flag(args, (char **)(&format), &count);
			ft_conversion(args, (char *)format, &count);
		}
		else
			ft_putchar(*format, &count);
		if (*format)
			format++;
	}
	va_end(args);
	return (count);
}
