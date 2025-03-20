/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:03:33 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/20 14:18:14 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atoi_part(const char **str)
{
	double	res;

	res = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		res = res * 10 + (**str - '0');
		(*str)++;
	}
	return (res);
}

double	ft_atod(const char *str)
{
	double (res), (sign), (decimal_place);
	res = ((sign = 1.0, decimal_place = 1.0), 0.0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1.0;
		str++;
	}
	res = ft_atoi_part(&str);
	if (*str == '.' && *(str + 1) != '\0')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			decimal_place *= 0.1;
			res += (*str - '0') * decimal_place;
			str++;
		}
	}
	if (*str || res > 2147483647.0 || res < -2147483648.0)
		exit(EXIT_FAILURE);
	return (res * sign);
}
