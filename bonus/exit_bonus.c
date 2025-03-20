/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:21:37 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/20 14:21:44 by mourhouc         ###   ########.fr       */
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

void	print_help(void)
{
	ft_printf("\033[30mFractol Controls: \033[0m\n");
	ft_printf("  1, 2, 3: Switch between Mandelbrot, Julia, and Burning Ship\n");
	ft_printf("  Arrow keys: Move around\n");
	ft_printf("  Scroll wheel: Zoom in/out\n");
	ft_printf("  +/- : Increase/decrease iterations\n");
	ft_printf("  C: Change color scheme\n");
	ft_printf("  ESC: Quit\n");
	ft_printf("  H: Show this help\n");
}

void	zoom(t_fractol *fractol, int x, int y, double factor)
{
	double		mouse_r;
	double		mouse_i;
	double		new_width;
	double		new_height;
	t_complex	z;

	pixel_to_complex(fractol, x, y, &z);
	mouse_r = z.r;
	mouse_i = z.i;
	new_width = (fractol->max_r - fractol->min_r) / factor;
	new_height = (fractol->max_i - fractol->min_i) / factor;
	fractol->min_r = mouse_r - (mouse_r - fractol->min_r) / factor;
	fractol->max_r = fractol->min_r + new_width;
	fractol->min_i = mouse_i - (mouse_i - fractol->min_i) / factor;
	fractol->max_i = fractol->min_i + new_height;
}
