/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:06:06 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/20 14:19:55 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	render_fractol(t_fractol *fractol)
{
	if (fractol->fractal_type == MANDELBROT)
		draw_mandelbrot(fractol);
	else if (fractol->fractal_type == JULIA)
		draw_julia(fractol);
}

void	zoom(t_fractol *fractol, int x, int y, double factor)
{
	double	center_r;
	double	center_i;
	double	new_width;
	double	new_height;

	(void)x;
	(void)y;
	center_r = (fractol->min_r + fractol->max_r) / 2;
	center_i = (fractol->min_i + fractol->max_i) / 2;
	new_width = (fractol->max_r - fractol->min_r) / factor;
	new_height = (fractol->max_i - fractol->min_i) / factor;
	fractol->min_r = center_r - new_width / 2;
	fractol->max_r = center_r + new_width / 2;
	fractol->min_i = center_i - new_height / 2;
	fractol->max_i = center_i + new_height / 2;
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

int	handle_key(int key, t_fractol *fractol)
{
	if (key == 53)
		close_window(fractol);
	else if (key == 18)
		fractol->fractal_type = MANDELBROT;
	else if (key == 19)
		fractol->fractal_type = JULIA;
	else if (key == 69)
		fractol->max_iter += 10;
	else if (key == 78 && fractol->max_iter > 10)
		fractol->max_iter -= 10;
	else if (key == 8)
		fractol->color_scheme = (fractol->color_scheme + 1) % 3;
	else if (key == 4)
		print_help();
	render_fractol(fractol);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;
	int			type;

	type = 0;
	arg_parse(argc, argv, &fractol);
	if ((ft_strlen(argv[1]) == 10) 
		&& (ft_strncmp(argv[1], "Mandelbrot", 10) == 0))
		type = MANDELBROT;
	else if ((ft_strlen(argv[1]) == 5) 
		&& (ft_strncmp(argv[1], "Julia", 5) == 0))
		type = JULIA;
	else
	{
		ft_printf("\033[31mInvalid type!\033[0m\ntype: 1 - Mandelbrot, 2 - Julia");
		exit(EXIT_FAILURE);
	}
	init_fractol(&fractol, type);
	print_help();
	render_fractol(&fractol);
	mlx_key_hook(fractol.win, handle_key, &fractol);
	mlx_mouse_hook(fractol.win, handle_mouse, &fractol);
	mlx_hook(fractol.win, 17, 0, close_window, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}
