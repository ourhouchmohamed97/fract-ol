/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:24:44 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/20 14:20:18 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	malloc_error(void)
{
	perror("\033[31mMalloc Error! \033[0m");
	exit(EXIT_FAILURE);
}

void	cleanup_fractol(t_fractol *fractol)
{
	if (fractol->img.img)
		mlx_destroy_image(fractol->mlx, fractol->img.img);
	if (fractol->win)
		mlx_destroy_window(fractol->mlx, fractol->win);
	ft_printf("\033[32mProgram quit successfully !\033[0m\n");
	exit(EXIT_SUCCESS);
}

int	close_window(t_fractol *fractol)
{
	cleanup_fractol(fractol);
	return (0);
}
