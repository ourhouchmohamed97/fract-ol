/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:39:49 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/17 11:02:18 by mourhouc         ###   ########.fr       */
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
			break ;
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
void	pixel_to_complex(t_fractol *fractol, int x, int y, t_complex *z)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = fractol->min_r;
	b = fractol->min_i;
	c = fractol->max_r;
	d = fractol->max_i;
	z->r = a + (double)x / (fractol->width - 1) * (c - a);
	z->i = b + (double)y / (fractol->height - 1) * (d - b);
}

/*
** This function draws the Mandelbrot set
*/
void	draw_mandelbrot(t_fractol *fractol)
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
			iter = mandelbrot_iteration(z.r, z.i, fractol->max_iter);
			color = get_color(iter, fractol->max_iter, fractol->color_scheme);
			put_pixel_to_image(fractol, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}

/*
** This function initializes the Mandelbrot view
*/
void	init_mandelbrot(t_fractol *fractol)
{
	fractol->min_r = -2.0;
	fractol->max_r = 1.0;
	fractol->min_i = -1.5;
	fractol->max_i = 1.5;
	fractol->max_iter = 100;
	fractol->zoom_factor = 1.1;
	fractol->fractal_type = MANDELBROT;
	fractol->color_scheme = 0;
}
