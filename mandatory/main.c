/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:06:06 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/11 14:10:58 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// void	mandelbrot_set(int argc, char **argv)
// {
// 	ft_printf("This is Mandelbrot set");
// }

// void	julia_set(int argc, char **argv)
// {
// 	ft_printf("This is Julia set");
// }

// int main(int argc, char **argv)
// {
// 	if (argc < 2)
// 	{
// 		ft_printf("you should enter at least 2 argument!");
// 		exit(1);
// 	}
// 	if (ft_strncmp(argv[1], "Mandelbrot", 11) == 0 && argc == 2)
// 		mandelbrot_set(argc, argv);
// 	else if (ft_strncmp(argv[1], "Julia", 6) == 0 && argc == 2)
// 		julia_set(argc, argv);
// 	else
// 		ft_printf("invalid fractal");
// }

/*
** Initialize the MLX library and create window
*/
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
    fractol->img = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
    if (!fractol->img)
    {
        mlx_destroy_window(fractol->mlx, fractol->win);
        free(fractol->mlx);
        malloc_error();
    }
    fractol->addr = mlx_get_data_addr(fractol->img, &fractol->bits_per_pixel,
                                      &fractol->line_length, &fractol->endian);
}

void init_fractol(t_fractol *fractol, int type)
{
    init_mlx(fractol); // set up graphic environment
    if (type == MANDELBROT)
        init_mandelbrot(fractol);
    else if (type == JULIA)
        init_julia(fractol);
}

void render_fractol(t_fractol *fractol)
{
    if (fractol->fractal_type == MANDELBROT)
        draw_mandelbrot(fractol);
    else if (fractol->fractal_type == JULIA)
        draw_julia(fractol);
}

/*
** Put a pixel to the image
*/
void put_pixel_to_image(t_fractol *fractol, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < fractol->width && y >= 0 && y < fractol->height)
    {
        dst = fractol->addr + (y * fractol->line_length +
                               x * (fractol->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
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

/*
** Handle keyboard input
*/
int handle_key(int key, t_fractol *fractol)
{
    if (key == 53) // ESC key
        cleanup_fractol(fractol);
    else if (key == 18) // 1 key - switch to Mandelbrot
        fractol->fractal_type = MANDELBROT;
    else if (key == 19) // 2 key - switch to Julia
        fractol->fractal_type = JULIA;
    else if (key == 123) // Left arrow - move left
        fractol->min_r -= 0.1 * (fractol->max_r - fractol->min_r);
    else if (key == 124) // Right arrow - move right
        fractol->min_r += 0.1 * (fractol->max_r - fractol->min_r);
    else if (key == 125) // Down arrow - move down
        fractol->min_i += 0.1 * (fractol->max_i - fractol->min_i);
    else if (key == 126) // Up arrow - move up
        fractol->min_i -= 0.1 * (fractol->max_i - fractol->min_i);
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

/*
** Handle mouse button press (zoom)
*/
int handle_mouse(int button, int x, int y, t_fractol *fractol)
{
    if (button == 4) // Scroll up - zoom in
        zoom(fractol, x, y, fractol->zoom_factor);
    else if (button == 5) // Scroll down - zoom out
        zoom(fractol, x, y, 1 / fractol->zoom_factor);
    render_fractol(fractol);
    return (0);
}

/*
** Handle mouse movement (for Julia set)
*/
int handle_mouse_move(int x, int y, t_fractol *fractol)
{
    if (fractol->fractal_type == JULIA)
    {
        // Only update if the mouse has moved significantly
        if (abs(fractol->mouse_x - x) > 10 || abs(fractol->mouse_y - y) > 10)
        {
            fractol->mouse_x = x;
            fractol->mouse_y = y;
            double c[2];
            pixel_to_complex(fractol, x, y, c);
            fractol->julia_r = c[0];
            fractol->julia_i = c[1];
            render_fractol(fractol);
        }
    }
    return (0);
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

/*
** Main function
*/
int main(int argc, char **argv)
{
    t_fractol   fractol;
    int         type;

    type = 0;
    if (argc == 2)
    {
        if ((ft_strlen(argv[1]) == 10) && (ft_strncmp(argv[1], "Mandelbrot", 10) == 0))
            type = MANDELBROT;
        else if ((ft_strlen(argv[1]) == 5) && (ft_strncmp(argv[1], "Julia", 5) == 0))
            type = JULIA;
        else
        {
            ft_printf("\033[31mError: Invalid type !\033[0m\n");
            ft_printf("     type: 1 - Mandelbrot, 2 - Julia\n");
            return (1);
        }
        init_fractol(&fractol, type);
        print_help();
        render_fractol(&fractol);
        mlx_key_hook(fractol.win, handle_key, &fractol);
        mlx_mouse_hook(fractol.win, handle_mouse, &fractol);
        mlx_hook(fractol.win, 6, 0, handle_mouse_move, &fractol);
        mlx_hook(fractol.win, 17, 0, close_window, &fractol);
        mlx_loop(fractol.mlx);
    }
    else
    {
        ft_printf("Usage: ./fractol <type>\n");
        ft_printf("You should enter 2 arguments\n");
    }
    return (0);
}
