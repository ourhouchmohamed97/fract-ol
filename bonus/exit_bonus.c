/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:21:37 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/15 19:21:39 by mourhouc         ###   ########.fr       */
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
	free(fractol->mlx);
	ft_printf("\033[32mProgram quit successfully !\033[0m\n");
	exit(EXIT_SUCCESS);
}

/*
** Handle window close event (X button)
*/

int	close_window(t_fractol *fractol)
{
	cleanup_fractol(fractol);
	return (0);
}