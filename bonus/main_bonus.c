/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:06:06 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/18 08:25:49 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

void	arrow_key(int key, t_fractol *fractol)
{
	double (shift_r), (shift_i);
	shift_r = 0.1 * (fractol->max_r - fractol->min_r);
	shift_i = 0.1 * (fractol->max_i - fractol->min_i);
	if (key == 123)
	{
		fractol->min_r += shift_r;
		fractol->max_r += shift_r;
	}
	else if (key == 124)
	{
		fractol->min_r -= shift_r;
		fractol->max_r -= shift_r;
	}
	else if (key == 125)
	{
		fractol->min_i -= shift_i;
		fractol->max_i -= shift_i;
	}
	else if (key == 126)
	{
		fractol->min_i += shift_i;
		fractol->max_i += shift_i;
	}
}

int	handle_key(int key, t_fractol *fractol)
{
	if (key == 53)
		close_window(fractol);
	else if (key == 18)
		fractol->fractal_type = MANDELBROT;
	else if (key == 19)
		fractol->fractal_type = JULIA;
	else if (key == 20)
		fractol->fractal_type = BURNING;
	else if (key == 123 || key == 124 || key == 125 || key == 126)
		arrow_key(key, fractol);
	else if (key == 24)
		fractol->max_iter += 10;
	else if (key == 27 && fractol->max_iter > 10)
		fractol->max_iter -= 10;
	else if (key == 8)
		fractol->color_scheme = (fractol->color_scheme + 1) % 3;
	else if (key == 4)
		print_help();
	render_fractol(fractol);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fractol *fractol)
{
	if (button == 4)
		zoom(fractol, x, y, fractol->zoom_factor);
	else if (button == 5)
		zoom(fractol, x, y, 1 / fractol->zoom_factor);
	render_fractol(fractol);
	return (0);
}

int	handle_mouse_move(int x, int y, t_fractol *fractol)
{
	t_complex	z;

	if (fractol->fractal_type == JULIA)
	{
		if (abs(fractol->mouse_x - x) > 10 || abs(fractol->mouse_y - y) > 10)
		{
			fractol->mouse_x = x;
			fractol->mouse_y = y;
			pixel_to_complex(fractol, x, y, &z);
			fractol->julia_r = z.r;
			fractol->julia_i = z.i;
			render_fractol(fractol);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	int (type), (len);
	arg_parse(argc, argv, &fractol);
	len = ((type = 0), ft_strlen(argv[1]));
	if ((len == 10) && (ft_strncmp(argv[1], "Mandelbrot", 10) == 0))
		type = MANDELBROT;
	else if ((len == 5) && (ft_strncmp(argv[1], "Julia", 5) == 0))
		type = JULIA;
	else if ((len == 7) && (ft_strncmp(argv[1], "Burning", 7) == 0))
		type = BURNING;
	else
	{
		ft_printf ("Invalid type!\ntype: Mandelbrot, Julia, Burning");
		exit(EXIT_FAILURE);
	}
	init_fractol(&fractol, type);
	print_help();
	render_fractol(&fractol);
	mlx_key_hook(fractol.win, handle_key, &fractol);
	mlx_mouse_hook(fractol.win, handle_mouse, &fractol);
	mlx_hook(fractol.win, 6, 0, handle_mouse_move, &fractol);
	mlx_hook(fractol.win, 17, 0, close_window, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}
