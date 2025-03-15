/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:45:11 by mourhouc          #+#    #+#             */
/*   Updated: 2025/03/15 19:19:09 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# include "../minilibx/mlx.h"
# include "../libft_utils/libft/libft.h"
# include "../libft_utils/printf/ft_printf.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 800

# define MANDELBROT 1
# define JULIA 2
# define BURNING_SHIP 3

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef	struct	s_img
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
int		julia_iteration(t_complex z, double cr, double ci, int max_iter);
/* Utility Functions */
void	pixel_to_complex(t_fractol *fractol, int x, int y, double *c);
void	zoom(t_fractol *fractol, int x, int y, double factor);
void	put_pixel_to_image(t_fractol *fractol, int x, int y, int color);
int		get_color(int iter, int max_iter, int color_scheme);
void	print_help(void);
void	init_mlx(t_fractol *fractol);

// ============== exit.c ===============
int		close_window(t_fractol *fractol);
void	cleanup_fractol(t_fractol *fractol);
void	malloc_error(void);
void	arg_parse(int argc, char **argv, t_fractol *fractol);

int		burning_ship_iteration(double cr, double ci, int max_iter);
void	draw_burning_ship(t_fractol *fractol);
void	init_burning_ship(t_fractol *fractol);


#endif