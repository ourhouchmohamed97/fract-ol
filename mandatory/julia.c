/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:25:02 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/20 14:20:09 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	julia_iteration(t_complex z, double cr, double ci, int max_iter)
{
	double	tmp;
	int		i;

	i = 0;
	while (i < max_iter)
	{
		if (z.r * z.r + z.i * z.i > 4.0)
			break ;
		tmp = z.r * z.r - z.i * z.i + cr;
		z.i = 2 * z.r * z.i + ci;
		z.r = tmp;
		i++;
	}
	return (i);
}

void	draw_julia(t_fractol *fractol)
{
	int			x;
	int			y;
	int			iter;
	int			color;
	t_complex	z;

	y = 0;
	while (y < fractol->height)
	{
		x = 0;
		while (x < fractol->width)
		{
			pixel_to_complex(fractol, x, y, &z);
			iter = julia_iteration(z, fractol->julia_r, 
					fractol->julia_i, fractol->max_iter);
			color = get_color(iter, fractol->max_iter, fractol->color_scheme);
			put_pixel_to_image(fractol, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}

void	init_julia(t_fractol *fractol)
{
	fractol->min_r = -2.0;
	fractol->max_r = 2.0;
	fractol->min_i = -2.0;
	fractol->max_i = 2.0;
	fractol->max_iter = 100;
	fractol->zoom_factor = 1.1;
	fractol->fractal_type = JULIA;
	fractol->color_scheme = 0;
}
