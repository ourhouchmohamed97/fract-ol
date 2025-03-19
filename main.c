/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:19:42 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/19 15:24:46 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft_utils/libft/libft.h"

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

// double	ft_atod(const char *str)
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
// 	res = ft_atoi_part(&str);
// 	if (*str == '.')
// 	{
// 		str++;
// 		while (*str >= '0' && *str <= '9')
// 		{
// 			decimal_place *= 0.1;
// 			res += (*str - '0') * decimal_place;
// 			str++;
// 			if ((res > 2147483647.0 && sign == 1.0) || (res > 2147483648.0 && sign == -1.0))
// 				exit(EXIT_FAILURE);
// 		}
// 	}
// 	if (*str)
// 		exit(EXIT_FAILURE);
// 	return (res * sign);
// }

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
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			decimal_place *= 0.1;
			res += (*str - '0') * decimal_place;
			str++;
		}
	}
	if (*str)
		return (0.0);
	return (res * sign);
}

int main()
{
	printf("%f\n", ft_atod("-0.835"));
	printf("%f", ft_atod("0.2321"));

	// char *p = "hello";
	// printf("%c\n",*(++p));
	// printf("%s\n",p);
}