/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:39:49 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/13 10:37:02 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

/*
** This function calculates if a point is in the Mandelbrot set
** It returns the number of iterations before escaping, or max_iter
*/
int	mandelbrot_iteration(double cr, double ci, int max_iter)
{
	double	zr;
	double	zi;
	double	tmp;
	int		i;

	zr = 0;
	zi = 0;
	i = 0;
	while (i < max_iter)
	{
		if (zr * zr + zi * zi > 4.0)
			break ;  // The point escapes, not in the Mandelbrot set
		tmp = zr * zr - zi * zi + cr;
		zi = 2 * zr * zi + ci;
		zr = tmp;
		i++;
	}
	return (i);
}

/*
** This function maps from pixel coordinates to complex plane coordinates
*/
void	pixel_to_complex(t_fractol *fractol, int x, int y, double *c)
{
	c[0] = fractol->min_r + (double)x / (fractol->width - 1) * (fractol->max_r - fractol->min_r);
	c[1] = fractol->min_i + (double)y / (fractol->height - 1) * (fractol->max_i - fractol->min_i);
}

/*
** This function draws the Mandelbrot set
*/
void	draw_mandelbrot(t_fractol *fractol)
{
	int		x;
	int		y;
	int		iter;
	double	c[2];  // c[0] = real part, c[1] = imaginary part
	int		color;

	y = 0;
	while (y < fractol->height)
	{
		x = 0;
		while (x < fractol->width)
		{
			pixel_to_complex(fractol, x, y, c);
			iter = mandelbrot_iteration(c[0], c[1], fractol->max_iter);
			color = get_color(iter, fractol->max_iter, fractol->color_scheme);
			put_pixel_to_image(fractol, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}

/*
** This function initializes the Mandelbrot view
*/
void	init_mandelbrot(t_fractol *fractol)
{
	double aspect_ratio;
	fractol->min_r = -2.0;
	fractol->max_r = 1.0;
	aspect_ratio = (double)fractol->height / fractol->width;
	fractol->min_i = -1.5 * aspect_ratio;
	fractol->max_i = 1.5 * aspect_ratio;
	fractol->max_iter = 100;
	fractol->zoom_factor = 1.1;
	fractol->fractal_type = MANDELBROT;
	fractol->color_scheme = 0;
}