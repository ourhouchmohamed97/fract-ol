/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:06:06 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/15 14:28:19 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void render_fractol(t_fractol *fractol)
{
    if (fractol->fractal_type == MANDELBROT)
        draw_mandelbrot(fractol);
    else if (fractol->fractal_type == JULIA)
        draw_julia(fractol);
}

void zoom(t_fractol *fractol, int x, int y, double factor)
{
    double center_re;
    double center_im;
    double new_width;
    double new_height;

    // For mandatory part, we ignore x and y and zoom on center
    (void)x;
    (void)y;

    // Calculate the center point
    center_re = fractol->min_r + (fractol->max_r - fractol->min_r) / 2.0;
    center_im = fractol->min_i + (fractol->max_i - fractol->min_i) / 2.0;

    // Calculate new dimensions
    new_width = (fractol->max_r - fractol->min_r) * factor;
    new_height = (fractol->max_i - fractol->min_i) * factor;

    // Set new boundaries centered on the center point
    fractol->min_r = center_re - new_width / 2.0;
    fractol->max_r = center_re + new_width / 2.0;
    fractol->min_i = center_im - new_height / 2.0;
    fractol->max_i = center_im + new_height / 2.0;
}

int handle_mouse(int button, int x, int y, t_fractol *fractol)
{
    if (button == 4) // Scroll up - zoom in
        zoom(fractol, x, y, fractol->zoom_factor);
    else if (button == 5) // Scroll down - zoom out
        zoom(fractol, x, y, 1 / fractol->zoom_factor);
    render_fractol(fractol);
    return (0);
}

int handle_key(int key, t_fractol *fractol)
{
    if (key == 53) // ESC key
        cleanup_fractol(fractol);
    else if (key == 18) // 1 key - switch to Mandelbrot
        fractol->fractal_type = MANDELBROT;
    else if (key == 19) // 2 key - switch to Julia
        fractol->fractal_type = JULIA;
    else if (key == 69) // + key - increase iterations
        fractol->max_iter += 10;
    else if (key == 78 && fractol->max_iter > 10) // - key - decrease iterations
        fractol->max_iter -= 10;
    else if (key == 8) // C key - change color scheme
        fractol->color_scheme = (fractol->color_scheme + 1) % 3;
    else if (key == 4) // H key - show help
        print_help();
    render_fractol(fractol);
    return (0);
}

int main(int argc, char **argv)
{
    t_fractol   fractol;
    int         type;

    type = 0;
    arg_parse(argc, argv, &fractol);
    if ((ft_strlen(argv[1]) == 10) && (ft_strncmp(argv[1], "Mandelbrot", 10) == 0))
        type = MANDELBROT;
    else if ((ft_strlen(argv[1]) == 5) && (ft_strncmp(argv[1], "Julia", 5) == 0))
        type = JULIA;
    else
    {
        ft_printf ("\033[31mInvalid type!\033[0m\ntype: 1 - Mandelbrot, 2 - Julia");
        exit (EXIT_FAILURE);
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