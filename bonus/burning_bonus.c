/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:24:26 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/20 12:10:17 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

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
			break ;
		tmp = zr * zr - zi * zi + cr;
		zi = fabs(2 * zr * zi) + ci;
		zr = tmp;
		i++;
	}
	return (i);
}

void	draw_burning_ship(t_fractol *fractol)
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
			iter = burning_ship_iteration(z.r, z.i, fractol->max_iter);
			color = get_color(iter, fractol->max_iter, fractol->color_scheme);
			put_pixel_to_image(fractol, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}

void	init_burning_ship(t_fractol *fractol)
{
	fractol->min_r = -2.0;
	fractol->max_r = 1.0;
	fractol->min_i = -2.0;
	fractol->max_i = 1.0;
	fractol->max_iter = 100;
	fractol->zoom_factor = 1.1;
	fractol->fractal_type = BURNING;
	fractol->color_scheme = 0;
}
