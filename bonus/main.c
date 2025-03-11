/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:06:06 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/08 17:03:03 by mourhouc         ###   ########.fr       */
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
	fractol->img = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
	if (!fractol->img)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		free(fractol->mlx);
		exit(1);
	}
	fractol->addr = mlx_get_data_addr(fractol->img, &fractol->bits_per_pixel,
									 &fractol->line_length, &fractol->endian);
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
		dst = fractol->addr + (y * fractol->line_length + 
				x * (fractol->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

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
		fractol->fractal_type = BURNING_SHIP;
	else if (key == 123)  // Left arrow - move left
		fractol->min_r -= 0.1 * (fractol->max_r - fractol->min_r);
	else if (key == 124)  // Right arrow - move right
		fractol->min_r += 0.1 * (fractol->max_r - fractol->min_r);
	else if (key == 125)  // Down arrow - move down
		fractol->min_i += 0.1 * (fractol->max_i - fractol->min_i);
	else if (key == 126)  // Up arrow - move up
		fractol->min_i -= 0.1 * (fractol->max_i - fractol->min_i);
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

/*
** Main function
*/
int	main(int argc, char **argv)
{
	t_fractol	fractol;
	int			type;

	type = MANDELBROT;  // Default
	if (argc >= 2)
	{
		if (argv[1][0] == '1' || argv[1][0] == 'm' || argv[1][0] == 'M')
			type = MANDELBROT;
		else if (argv[1][0] == '2' || argv[1][0] == 'j' || argv[1][0] == 'J')
			type = JULIA;
		else if (argv[1][0] == '3' || argv[1][0] == 'b' || argv[1][0] == 'B')
			type = BURNING_SHIP;
		else
		{
			write(1, "Usage: ./fractol [type]\n", 25);
			write(1, "  type: 1/m for Mandelbrot, 2/j for Julia, 3/b for Burning Ship\n", 64);
			return (1);
		}
	}
	init_fractol(&fractol, type);
	print_help();
	render_fractol(&fractol);
	mlx_key_hook(fractol.win, handle_key, &fractol);
	mlx_mouse_hook(fractol.win, handle_mouse, &fractol);
	mlx_hook(fractol.win, 6, 0, handle_mouse_move, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}
