// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   fractol.h                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/25 15:25:13 by mourhouc          #+#    #+#             */
// /*   Updated: 2025/03/01 09:42:31 by mourhouc         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef FRACTOL_H
// # define FRACTOL_H

// # include "../minilibx/mlx.h"
// # include "../libft_utils/libft/libft.h"
// # include "../libft_utils/printf/ft_printf.h"

// // mandelbrot_set(int argc, char **argv);
// // julia_set(int argc, char **argv);
// int	mandelbrot_iteration(double cr, double ci, int max_iter);
// void	pixel_to_complex(t_fractol *fractol, int x, int y, double *c);
// void	draw_mandelbrot(t_fractol *fractol);
// void	init_mandelbrot(t_fractol *fractol);
// int	get_color(int iter, int max_iter, int color_scheme);


// #endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/03/01 10:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 800

# define MANDELBROT 1
# define JULIA 2
# define BURNING_SHIP 3

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	int		max_iter;
	double	zoom_factor;
	int		fractal_type;
	int		color_scheme;
	double	julia_r;
	double	julia_i;
	int		mouse_x;
	int		mouse_y;
}	t_fractol;

/* Main Functions */
void	init_fractol(t_fractol *fractol, int type);
int		handle_key(int key, t_fractol *fractol);
int		handle_mouse(int button, int x, int y, t_fractol *fractol);
int		handle_mouse_move(int x, int y, t_fractol *fractol);
void	render_fractol(t_fractol *fractol);

/* Fractal Specific Functions */
void	init_mandelbrot(t_fractol *fractol);
void	draw_mandelbrot(t_fractol *fractol);
int		mandelbrot_iteration(double cr, double ci, int max_iter);

void	init_julia(t_fractol *fractol);
void	draw_julia(t_fractol *fractol);
int		julia_iteration(double zr, double zi, double cr, double ci, int max_iter);

void	init_burning_ship(t_fractol *fractol);
void	draw_burning_ship(t_fractol *fractol);
int		burning_ship_iteration(double cr, double ci, int max_iter);

/* Utility Functions */
void	pixel_to_complex(t_fractol *fractol, int x, int y, double *c);
void	zoom(t_fractol *fractol, int x, int y, double factor);
void	put_pixel_to_image(t_fractol *fractol, int x, int y, int color);
int		get_color(int iter, int max_iter, int color_scheme);
void	print_help(void);

void	init_mlx(t_fractol *fractol);
int	julia_iteration(double zr, double zi, double cr, double ci, int max_iter);
void	draw_julia(t_fractol *fractol);
void	init_julia(t_fractol *fractol);
void	init_burning_ship(t_fractol *fractol);
void	draw_burning_ship(t_fractol *fractol);
int	burning_ship_iteration(double cr, double ci, int max_iter);


#endif