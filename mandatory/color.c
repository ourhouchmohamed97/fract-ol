/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:41:47 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/13 12:09:28 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

/*
** Color scheme 0: Linear gradient from black to white
*/
static int	color_scheme_0(int iter, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == max_iter)
		return (0x000000);  // Black for points in the set
	t = (double)iter / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}

/*
** Color scheme 1: Psychedelic gradient
*/
static int	color_scheme_1(int iter, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == max_iter)
		return (0x000000);  // Black for points in the set
	t = (double)iter / max_iter;
	r = (int)(255 * sin(0.1 * iter + 0));
	g = (int)(255 * sin(0.1 * iter + 2));
	b = (int)(255 * sin(0.1 * iter + 4));
	return ((r << 16) | (g << 8) | b);
}

/*
** Color scheme 2: Smooth coloring using HSV
*/
static int	color_scheme_2(int iter, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;
	double	h;
	double	s;
	double	v;

	if (iter == max_iter)
		return (0x000000);  // Black for points in the set
	
	// Normalized iteration count (smooth coloring)
	t = (double)iter / max_iter;
	
	// HSV coloring
	h = 360.0 * t;
	s = 0.8;
	v = 1.0;
	
	// Convert HSV to RGB (simplified algorithm)
	int	hi = (int)(h / 60) % 6;
	double f = h / 60 - hi;
	double p = v * (1 - s);
	double q = v * (1 - f * s);
	double u = v * (1 - (1 - f) * s);
	
	switch (hi)
	{
		case 0: r = v * 255; g = u * 255; b = p * 255; break;
		case 1: r = q * 255; g = v * 255; b = p * 255; break;
		case 2: r = p * 255; g = v * 255; b = u * 255; break;
		case 3: r = p * 255; g = q * 255; b = v * 255; break;
		case 4: r = u * 255; g = p * 255; b = v * 255; break;
		case 5: r = v * 255; g = p * 255; b = q * 255; break;
	}
	
	return ((r << 16) | (g << 8) | b);
}

/*
** Get the color based on the iteration and chosen color scheme
*/
int	get_color(int iter, int max_iter, int color_scheme)
{
	if (color_scheme == 0)
		return (color_scheme_0(iter, max_iter));
	else if (color_scheme == 1)
		return (color_scheme_1(iter, max_iter));
	else if (color_scheme == 2)
		return (color_scheme_2(iter, max_iter));
	else
		return (color_scheme_0(iter, max_iter));  // Default
}