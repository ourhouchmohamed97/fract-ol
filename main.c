#include "minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define SIZE 800 // Define the size of the window

typedef struct s_fractal
{
	void *mlx;
	void *window;
	void *image;
	int x;
	int y;
	double zx;
	double zy;
	double cx;
	double cy;
	double zoom;
	double offset_x;
	double offset_y;
	int max_iterations;
	int color;
	char *name;
} t_fractal;


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void put_color_to_pixel(t_fractal *fractal, int x, int y, int color)
{

	char *img_data;
	img_data = mlx_get_data_addr(fractal->image, &(int){0}, &(int){0}, &(int){0});
	*(int *)(img_data + (y * SIZE + x) * sizeof(int)) = color;
}

void exit_fractal(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->image);
	mlx_destroy_window(fractal->mlx, fractal->window);
	free(fractal);
	exit(0);
}

void calculate_mandelbrot(t_fractal *fractal)
{
	int i;
	double x_temp;
	fractal->name = "mandel";
	i = 0;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = (fractal->x / fractal->zoom) + fractal->offset_x;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->offset_y;
	while (++i < fractal->max_iterations)
	{
		x_temp = fractal->zx * fractal->zx - fractal->zy * fractal->zy + fractal->cx;
		fractal->zy = 2.0 * fractal->zx * fractal->zy + fractal->cy;
		fractal->zx = x_temp;
		if (fractal->zx * fractal->zx + fractal->zy * fractal->zy >= __DBL_MAX__)
			break;
	}
	if (i == fractal->max_iterations)
		put_color_to_pixel(fractal, fractal->x, fractal->y, 0x000000);
	else
		put_color_to_pixel(fractal, fractal->x, fractal->y, (fractal->color * i));
}

void calculate_julia(t_fractal *fractal, double cx, double cy)
{
	int i;
	double tmp;
	fractal->name = "julia";
	fractal->cx = cx;
	fractal->cy = cy;
	fractal->zx = fractal->x / fractal->zoom + fractal->offset_x;
	fractal->zy = fractal->y / fractal->zoom + fractal->offset_y;
	i = 0;
	while (++i < fractal->max_iterations)
	{
		tmp = fractal->zx;
		fractal->zx = fractal->zx * fractal->zx - fractal->zy * fractal->zy + fractal->cx;
		fractal->zy = 2 * fractal->zy * tmp + fractal->cy;
		if (fractal->zx * fractal->zx + fractal->zy * fractal->zy >= __DBL_MAX__)
			break;
	}
	if (i == fractal->max_iterations)
		put_color_to_pixel(fractal, fractal->x, fractal->y, 0x000000);
	else
		put_color_to_pixel(fractal, fractal->x, fractal->y, (fractal->color * (i % 255)));
}

void calculate_burning_ship(t_fractal *fractal)
{
	int i;
	double x_temp;
	fractal->name = "ship";
	i = 0;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = (fractal->x / fractal->zoom) + fractal->offset_x;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->offset_y;
	while (++i < fractal->max_iterations)
	{
		x_temp = fractal->zx * fractal->zx - fractal->zy * fractal->zy + fractal->cx;
		fractal->zy = fabs(2.0 * fractal->zx * fractal->zy) + fractal->cy;
		fractal->zx = fabs(x_temp);
		if (fractal->zx * fractal->zx + fractal->zy * fractal->zy >= __DBL_MAX__)
			break;
	}
	if (i == fractal->max_iterations)
		put_color_to_pixel(fractal, fractal->x, fractal->y, 0x000000);
	else
		put_color_to_pixel(fractal, fractal->x, fractal->y, (fractal->color * i));
}

int draw_fractal(t_fractal *fractal, char *query, double cx, double cy)
{
	fractal->x = 0;
	fractal->y = 0;
	while (fractal->x < SIZE)
	{
		while (fractal->y < SIZE)
		{
			if (ft_strncmp(query, "mandel", 7) == 0)
				calculate_mandelbrot(fractal);
			else if (ft_strncmp(query, "julia", 6) == 0)
				calculate_julia(fractal, cx, cy);
			else if (ft_strncmp(query, "ship", 5) == 0)
				calculate_burning_ship(fractal);
			else
			{
				fprintf(stderr, "Available fractals: mandel, julia, ship\n");
				exit_fractal(fractal);
			}
			fractal->y++;
		}
		fractal->x++;
		fractal->y = 0;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0, 0);
	return 0;
}

int main(int argc, char **argv)
{
	t_fractal fractal;

	// Initialize the fractal structure
	fractal.mlx = mlx_init();
	fractal.window = mlx_new_window(fractal.mlx, SIZE, SIZE, "Fractal Viewer");
	fractal.image = mlx_new_image(fractal.mlx, SIZE, SIZE);
	fractal.zoom = 1.0;
	fractal.offset_x = 0.0;
	fractal.offset_y = 0.0;
	fractal.max_iterations = 100; // Set the maximum iterations
	fractal.color = 0xFCBE11;	  // Set a default color
	// Check for the correct number of arguments
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <fractal_type> [cx] [cy]\n", argv[0]);
		return 1;
	}
	// Parse the fractal type and optional parameters
	char *fractal_type = argv[1];
	double cx = (argc > 2) ? atof(argv[2]) : 0.0; // Default cx for Julia
	double cy = (argc > 3) ? atof(argv[3]) : 0.0; // Default cy for Julia
	// Draw the selected fractal
	draw_fractal(&fractal, fractal_type, cx, cy);
	// Display the image in the window
	mlx_put_image_to_window(fractal.mlx, fractal.window, fractal.image, 0, 0);
	// Event loop to keep the window open
	mlx_loop(fractal.mlx);
	// Clean up and exit
	exit_fractal(&fractal);
	return 0;
}