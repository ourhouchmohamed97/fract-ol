/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:52:22 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/17 17:49:52 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

void	init_mlx(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		malloc_error();
	fractol->width = WIN_WIDTH;
	fractol->height = WIN_HEIGHT;
	fractol->win = mlx_new_window(fractol->mlx, fractol->width, 
			fractol->height, "Fractol");
	if (!fractol->win)
	{
		free(fractol->mlx);
		malloc_error();
	}
	fractol->img.img = mlx_new_image(fractol->mlx, 
			fractol->width, fractol->height);
	if (!fractol->img.img)
	{
		mlx_destroy_image(fractol->mlx, fractol->img.img);
		mlx_destroy_window(fractol->mlx, fractol->win);
		free(fractol->mlx);
		malloc_error();
	}
	fractol->img.addr = mlx_get_data_addr(fractol->img.img, 
			&fractol->img.bits_per_pixel, &fractol->img.line_length, 
			&fractol->img.endian);
}

void	init_fractol(t_fractol *fractol, int type)
{
	init_mlx(fractol);
	if (type == MANDELBROT)
		init_mandelbrot(fractol);
	else if (type == JULIA)
		init_julia(fractol);
	else if (type == BURNING)
		init_burning_ship(fractol);
}

void	render_fractol(t_fractol *fractol)
{
	if (fractol->fractal_type == MANDELBROT)
		draw_mandelbrot(fractol);
	else if (fractol->fractal_type == JULIA)
		draw_julia(fractol);
	else if (fractol->fractal_type == BURNING)
		draw_burning_ship(fractol);
}

void	put_pixel_to_image(t_fractol *fractol, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < fractol->width && y >= 0 && y < fractol->height)
	{
		dst = fractol->img.addr + (y * fractol->img.line_length + 
				x * (fractol->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	arg_parse(int argc, char **argv, t_fractol *fractol)
{
	if (argc < 2)
	{
		ft_printf("Usage: ./fractol <type>\n");
		ft_printf("You should enter at least 2 arguments\n");
		exit(EXIT_FAILURE);
	}
	if (argc == 4 && (ft_strlen(argv[1]) == 5) 
		&& (ft_strncmp(argv[1], "Julia", 5) == 0))
	{
		fractol->julia_r = ft_atod(argv[2]);
		fractol->julia_i = ft_atod(argv[3]);
	}
	else if (argc == 2)
	{
		fractol->julia_r = -0.7269;
		fractol->julia_i = 0.1889;
	}
	else
	{
		ft_printf("\033[31mError: Too many arguments !\033[0m\n");
		exit(EXIT_FAILURE);
	}
}
