/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:06:06 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/15 21:47:50 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"
/*
** Zoom in or out based on mouse position
*/
void	zoom(t_fractol *fractol, int x, int y, double factor)
{
	double	mouse_r;
	double	mouse_i;
	double	c[2];

	pixel_to_complex(fractol, x, y, c);
	mouse_r = c[0];
	mouse_i = c[1];
	
	double new_width = (fractol->max_r - fractol->min_r) / factor;
	double new_height = (fractol->max_i - fractol->min_i) / factor;
	
	fractol->min_r = mouse_r - (mouse_r - fractol->min_r) / factor;
	fractol->max_r = fractol->min_r + new_width;
	fractol->min_i = mouse_i - (mouse_i - fractol->min_i) / factor;
	fractol->max_i = fractol->min_i + new_height;
}

// void zoom(t_fractol *fractol, int x, int y, double factor)
// {
//     double center_re;
//     double center_im;
//     double new_width;
//     double new_height;
    
//     // For mandatory part, we ignore x and y and zoom on center
//     (void)x;
//     (void)y;
    
//     // Calculate the center point
//     center_re = fractol->min_re + (fractol->max_re - fractol->min_re) / 2.0;
//     center_im = fractol->min_im + (fractol->max_im - fractol->min_im) / 2.0;
    
//     // Calculate new dimensions
//     new_width = (fractol->max_re - fractol->min_re) * factor;
//     new_height = (fractol->max_im - fractol->min_im) * factor;
    
//     // Set new boundaries centered on the center point
//     fractol->min_re = center_re - new_width / 2.0;
//     fractol->max_re = center_re + new_width / 2.0;
//     fractol->min_im = center_im - new_height / 2.0;
//     fractol->max_im = center_im + new_height / 2.0;
    
//     // Redraw the fractal
//     draw_fractol(fractol);
// }

/*
** Handle keyboard input
*/
int	handle_key(int key, t_fractol *fractol)
{
	double  shift;
	if (key == 53)  // ESC key
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		exit(0);
	}
	else if (key == 18)  // 1 key - switch to Mandelbrot
		fractol->fractal_type = MANDELBROT;
	else if (key == 19)  // 2 key - switch to Julia
		fractol->fractal_type = JULIA;
	else if (key == 20)  // 3 key - switch to Burning Ship
		fractol->fractal_type = BURNING;
	else if (key == 123) // Left arrow - move left
    {
        shift = 0.1 * (fractol->max_r - fractol->min_r);
        fractol->min_r += shift;
        fractol->max_r += shift;
    }
    else if (key == 124) // Right arrow - move right
    {
        shift = 0.1 * (fractol->max_r - fractol->min_r);
        fractol->min_r -= shift;
        fractol->max_r -= shift;
    }
    else if (key == 125) // Down arrow - move down
    {
        shift = 0.1 * (fractol->max_i - fractol->min_i);
        fractol->min_i -= shift;
        fractol->max_i -= shift;
    }
    else if (key == 126) // Up arrow - move up
    {
        shift = 0.1 * (fractol->max_i - fractol->min_i);
        fractol->min_i += shift;
        fractol->max_i += shift;
    }
	else if (key == 24)  // + key - increase iterations
		fractol->max_iter += 10;
	else if (key == 27 && fractol->max_iter > 10)  // - key - decrease iterations
		fractol->max_iter -= 10;
	else if (key == 8)  // C key - change color scheme
		fractol->color_scheme = (fractol->color_scheme + 1) % 3;
	else if (key == 49)  // Space key - reset view
		init_fractol(fractol, fractol->fractal_type);
	else if (key == 4)  // H key - show help
		print_help();
	render_fractol(fractol);
	return (0);
}

/*
** Handle mouse button press (zoom)
*/
int	handle_mouse(int button, int x, int y, t_fractol *fractol)
{
	if (button == 4)  // Scroll up - zoom in
		zoom(fractol, x, y, fractol->zoom_factor);
	else if (button == 5)  // Scroll down - zoom out
		zoom(fractol, x, y, 1 / fractol->zoom_factor);
	render_fractol(fractol);
	return (0);
}

/*
** Handle mouse movement (for Julia set)
*/
int	handle_mouse_move(int x, int y, t_fractol *fractol)
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
** Main function
*/
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
    else if ((ft_strlen(argv[1]) == 7) && (ft_strncmp(argv[1], "Burning", 7) == 0))
        type = BURNING;
    else
    {
        ft_printf ("\033[31mInvalid type!\033[0m\ntype: 1 - Mandelbrot, 2 - Julia 3 - Burning");
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
