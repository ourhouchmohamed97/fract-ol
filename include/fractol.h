/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/03/19 17:58:35 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx/mlx.h"
# include "../libft_utils/libft/libft.h"
# include "../libft_utils/printf/ft_printf.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 800

# define MANDELBROT 1
# define JULIA 2

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_img	img;
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

// ============== main.c ===============
void	render_fractol(t_fractol *fractol);
void	zoom(t_fractol *fractol, int x, int y, double factor);
int		handle_key(int key, t_fractol *fractol);
int		handle_mouse(int button, int x, int y, t_fractol *fractol);

// ============== init.c ===============
void	init_fractol(t_fractol *fractol, int type);
void	init_mlx(t_fractol *fractol);
void	put_pixel_to_image(t_fractol *fractol, int x, int y, int color);
void	arg_parse(int argc, char **argv, t_fractol *fractol);
void	print_help(void);

// ============== mandelbrot.c ===============
void	init_mandelbrot(t_fractol *fractol);
void	draw_mandelbrot(t_fractol *fractol);
int		mandelbrot_iteration(double cr, double ci, int max_iter);
void	pixel_to_complex(t_fractol *fractol, int x, int y, t_complex *z);

// ============== julia.c ===============
void	init_julia(t_fractol *fractol);
void	draw_julia(t_fractol *fractol);
int		julia_iteration(t_complex z, double cr, double ci, int max_iter);

// ============== exit.c ===============
int		close_window(t_fractol *fractol);
void	cleanup_fractol(t_fractol *fractol);
void	malloc_error(void);

// ============== color.c ===============
int		color_scheme_0(int iter, int max_iter);
int		color_scheme_1(int iter, int max_iter);
int		color_scheme_2(int iter, int max_iter);
int		get_color(int iter, int max_iter, int color_scheme);

#endif