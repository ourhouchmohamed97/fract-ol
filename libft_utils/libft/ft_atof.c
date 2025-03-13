/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:03:33 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/13 17:54:08 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// double	ft_atof(const char *str)
// {
// 	double	(res), (sign), (decimal_place);
// 	res = ((sign = 1.0, decimal_place = 1.0), 0.0);
// 	int	i;

// 	i = 0;
// 	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1.0;
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		res = res * 10 + (str[i] - '0');
// 		i++;
// 	}
// 	if (str[i] == '.')
// 	{
// 		i++;
// 		while (str[i] >= '0' && str[i] <= '9')
// 		{
// 			decimal_place *= 0.1;
// 			res += (str[i] - '0') * decimal_place;
// 			i++;
// 		}
// 	}
// 	return (res * sign);
// }

// double	ft_atof(const char *str)
// {
// 	double (res), (sign), (decimal_place);
// 	res = ((sign = 1.0, decimal_place = 1.0), 0.0);
// 	while (*str == ' ' || (*str >= 9 && *str <= 13))
// 		str++;
// 	if (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-')
// 			sign = -1.0;
// 		str++;
// 	}
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		res = res * 10 + (*str - '0');
// 		str++;
// 	}
// 	if (*str == '.')
// 	{
// 		str++;
// 		while (*str >= '0' && *str <= '9')
// 		{
// 			decimal_place *= 0.1;
// 			res += (*str - '0') * decimal_place;
// 			str++;
// 		}
// 	}
// 	return (res * sign);
// }

double	ft_atoi_part(const char *str, int *i)
{
	double	res;

	res = 0.0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		res = res * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (res);
}

double	ft_atof(const char *str)
{
	int	i;

	double (res), (sign), (decimal_place);
	res = ((sign = 1.0, decimal_place = 1.0), 0.0);
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	res = ft_atoi_part(str, &i);
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			decimal_place *= 0.1;
			res += (str[i] - '0') * decimal_place;
			i++;
		}
	}
	return (res * sign);
}
