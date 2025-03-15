/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:24:26 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/15 16:58:59 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

/*
** This function calculates if a point is in the Burning Ship fractal
** It returns the number of iterations before escaping, or max_iter
*/
int	burning_ship_iteration(double cr, double ci, int max_iter)
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
			break ;  // The point escapes, not in the set
		// The key difference from Mandelbrot is taking the absolute value
		// before squaring
		tmp = zr * zr - zi * zi + cr;
		zi = fabs(2 * zr * zi) + ci;  // Take absolute value here
		zr = tmp;
		i++;
	}
	return (i);
}
/*
** This function draws the Burning Ship fractal
*/
void	draw_burning_ship(t_fractol *fractol)
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
			iter = burning_ship_iteration(c[0], c[1], fractol->max_iter);
			color = get_color(iter, fractol->max_iter, fractol->color_scheme);
			put_pixel_to_image(fractol, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}

/*
** This function initializes the Burning Ship view
** The Burning Ship looks best with a slightly different initial view
*/
void	init_burning_ship(t_fractol *fractol)
{
	fractol->min_r = -2.0;
	fractol->max_r = 1.0;
	fractol->min_i = -2.0;
	fractol->max_i = 1.0;
	fractol->max_iter = 100;
	fractol->zoom_factor = 1.1;
	fractol->fractal_type = BURNING_SHIP;
	fractol->color_scheme = 0;
}