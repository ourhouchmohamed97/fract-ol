/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:41:47 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/20 14:20:21 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	color_scheme_0(int iter, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}

int	color_scheme_1(int iter, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / max_iter;
	r = (int)(t * 255);
	g = (int)((1 - t) * 255);
	b = (int)((1 - t) * 255);
	return ((r << 16) | (g << 8) | b);
}

int	color_scheme_2(int iter, int max_iter)
{
	double (t), (h), (s), (v), (f), (p), (q), (u);
	int (r), (g), (b), (hi);
	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / max_iter;
	h = 360.0 * t;
	s = ((v = 1.0), 0.8);
	hi = (int)(h / 60) % 6;
	f = h / 60 - hi;
	p = v * (1 - s);
	q = v * (1 - f * s);
	u = v * (1 - (1 - f) * s);
	if (hi == 0)
		b = ((r = v * 255, g = u * 255), p * 255);
	else if (hi == 1)
		b = ((r = q * 255, g = v * 255), p * 255);
	else if (hi == 2)
		b = ((r = p * 255, g = v * 255), u * 255);
	else if (hi == 3)
		b = ((r = p * 255, g = q * 255), v * 255);
	else if (hi == 4)
		b = ((r = u * 255, g = p * 255), v * 255);
	else
		b = ((r = v * 255, g = p * 255), q * 255);
	return ((r << 16) | (g << 8) | b);
}

int	get_color(int iter, int max_iter, int color_scheme)
{
	if (color_scheme == 0)
		return (color_scheme_0(iter, max_iter));
	else if (color_scheme == 1)
		return (color_scheme_1(iter, max_iter));
	else if (color_scheme == 2)
		return (color_scheme_2(iter, max_iter));
	else
		return (color_scheme_0(iter, max_iter));
}
