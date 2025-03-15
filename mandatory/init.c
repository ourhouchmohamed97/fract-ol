/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:38:41 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/15 11:14:59 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void init_mlx(t_fractol *fractol)
{
    fractol->mlx = mlx_init();
    if (!fractol->mlx)
        malloc_error();
    fractol->width = WIN_WIDTH;
    fractol->height = WIN_HEIGHT;
    fractol->win = mlx_new_window(fractol->mlx, fractol->width, fractol->height, "Fractol");
    if (!fractol->win)
    {
        free(fractol->mlx);
        malloc_error();
    }
    fractol->img.img = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
    if (!fractol->img.img)
    {
        mlx_destroy_window(fractol->mlx, fractol->win);
        free(fractol->mlx);
        malloc_error();
    }
    fractol->img.addr = mlx_get_data_addr(fractol->img.img, &fractol->img.bits_per_pixel,
                                      &fractol->img.line_length, &fractol->img.endian);
}

void init_fractol(t_fractol *fractol, int type)
{
    init_mlx(fractol); // set up graphic environment
    if (type == MANDELBROT)
        init_mandelbrot(fractol);
    else if (type == JULIA)
        init_julia(fractol);
}

/*
** Put a pixel to the image
*/
void put_pixel_to_image(t_fractol *fractol, int x, int y, int color)
{
    char *dst;

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
void print_help(void)
{
    ft_printf("\033[30mFractol Controls: \033[0m\n");
    ft_printf("  1, 2: Switch between Mandelbrot, Julia\n");
    ft_printf("  Arrow keys: Move around\n");
    ft_printf("  Scroll wheel: Zoom in/out\n");
    ft_printf("  +/- : Increase/decrease iterations\n");
    ft_printf("  C: Change color scheme\n");
    ft_printf("  ESC: Quit\n");
    ft_printf("  H: Show this help\n");
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
            fractol->julia_r = ft_atof(argv[2]);
            fractol->julia_i = ft_atof(argv[3]);
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