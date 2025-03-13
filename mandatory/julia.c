/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:25:02 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/13 11:20:56 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

/*
** This function calculates if a point is in the Julia set
** It returns the number of iterations before escaping, or max_iter
** Key difference from Mandelbrot: z starts as the point, c is constant
*/
int	julia_iteration(double zr, double zi, double cr, double ci, int max_iter)
{
	double	tmp;
	int		i;

	i = 0;
	while (i < max_iter)
	{
		if (zr * zr + zi * zi > 4.0)
			break ;  // The point escapes, not in the Julia set
		tmp = zr * zr - zi * zi + cr;
		zi = 2 * zr * zi + ci;
		zr = tmp;
		i++;
	}
	return (i);
}

/*
** This function draws the Julia set
*/
void	draw_julia(t_fractol *fractol)
{
	int		x;
	int		y;
	int		iter;
	double	c[2];  // Now c[0] = zr, c[1] = zi (the point to test)
	int		color;

	y = 0;
	while (y < fractol->height)
	{
		x = 0;
		while (x < fractol->width)
		{
			pixel_to_complex(fractol, x, y, c);
			// Call with c as the point to test, julia_r/i as the constant
			iter = julia_iteration(c[0], c[1], fractol->julia_r, fractol->julia_i, fractol->max_iter);
			color = get_color(iter, fractol->max_iter, fractol->color_scheme);
			put_pixel_to_image(fractol, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}

/*
** This function initializes the Julia set view
*/
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
	// Default Julia set parameters (can be changed with mouse)
	fractol->julia_r = -0.7;
	fractol->julia_i = 0.27015;
	fractol->mouse_x = 0;
	fractol->mouse_y = 0;
}