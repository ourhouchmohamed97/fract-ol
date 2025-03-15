/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:52:22 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/15 19:23:13 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"
/*
** Initialize the MLX library and create window
*/
void	init_mlx(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		exit(1);
	fractol->width = WIN_WIDTH;
	fractol->height = WIN_HEIGHT;
	fractol->win = mlx_new_window(fractol->mlx, fractol->width, fractol->height, "Fractol");
	if (!fractol->win)
	{
		free(fractol->mlx);
		exit(1);
	}
	fractol->img.img = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
	if (!fractol->img.img)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		free(fractol->mlx);
		exit(1);
	}
	fractol->img.addr = mlx_get_data_addr(fractol->img.img, &fractol->img.bits_per_pixel,
									 &fractol->img.line_length, &fractol->img.endian);
}

/*
** Initialize the fractol structure based on the fractal type
*/
void	init_fractol(t_fractol *fractol, int type)
{
	init_mlx(fractol); // set up graphic environment
	if (type == MANDELBROT)
		init_mandelbrot(fractol);
	else if (type == JULIA)
		init_julia(fractol);
	else if (type == BURNING_SHIP)
		init_burning_ship(fractol);
}


/*
** Render the appropriate fractal based on type
*/
void	render_fractol(t_fractol *fractol)
{
	if (fractol->fractal_type == MANDELBROT)
		draw_mandelbrot(fractol);
	else if (fractol->fractal_type == JULIA)
		draw_julia(fractol);
	else if (fractol->fractal_type == BURNING_SHIP)
		draw_burning_ship(fractol);
}

/*
** Put a pixel to the image
*/
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
/*
** Print help information
*/
void	print_help(void)
{
	write(1, "Fractol Controls:\n", 19);
	write(1, "  1, 2, 3: Switch between Mandelbrot, Julia, and Burning Ship\n", 61);
	write(1, "  Arrow keys: Move around\n", 26);
	write(1, "  Scroll wheel: Zoom in/out\n", 28);
	write(1, "  +/- : Increase/decrease iterations\n", 37);
	write(1, "  C: Change color scheme\n", 25);
	write(1, "  Space: Reset view\n", 21);
	write(1, "  ESC: Quit\n", 13);
	write(1, "  H: Show this help\n", 21);
}

void    arg_parse(int argc, char **argv, t_fractol *fractol)
{
    if (argc < 2)
    {
        ft_printf("Usage: ./fractol <type>\n");
        ft_printf("You should enter 2 arguments\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 4 && (ft_strlen(argv[1]) == 5) && (ft_strncmp(argv[1], "Julia", 5) == 0))
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