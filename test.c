#include "minilibx/mlx.h"
#include <math.h>

int destence(int x, int y, int cx, int cy, int dest)
{
	if (sqrt(pow(x - cx, 2) + pow(y - cy, 2)) < dest)
		return (1);
	return (0);
}
// int main()
// {
// 	void *mlx;
// 	void *mlx_win;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1000, 1000, "Cercle");
// 	int i = 0;
// 	int  j = 0;
// 	while (i < 1000)
// 	{
// 		j = 0;
// 		while ( j < 1000)
// 		{
// 			if (destence(i, j, 500, 500, 500))
// 			mlx_pixel_put(mlx, mlx_win, i, j, 0x00FFFFFF);
// 			// else 
// 			// mlx_pixel_put(mlx, mlx_win, i, j, 0x00000000);

// 			j++;
// 		}
// 		i++;
// 	}
// 	mlx_loop(mlx);
// }


// int main()
// {
// 	void *mlx;
// 	void *mlx_win;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1000, 1000, "Cercle");
// 	int i = 0;
// 	int  j = 0;
// 	while (i < 1000)
// 	{
// 		j = 0;
// 		while ( j < 1000)
// 		{
// 			if (i > 500 - j /2 && i < 500 + j / 2)
// 			mlx_pixel_put(mlx, mlx_win, i, j, 0x00FFFFFF);
// 			// else 
// 			// mlx_pixel_put(mlx, mlx_win, i, j, 0x00000000);

// 			j++;
// 		}
// 		i++;
// 	}
// 	mlx_loop(mlx);
// }



// int main()
// {
// 	void	*mlx;
// 	void	*win;
// 	int		x, y;
// 	int		pos_x = 100;
// 	int		pos_y = 100;
// 	int		size = 50;

// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 800, 400, "circle");

// 	y = 0;
// 	while (y < 1000)
// 	{
// 		x = 0;
// 		while (x < 1000)
// 		{
// 			int dx = x - pos_x;
// 			int dy = y - pos_y;
// 			if ((dx * dx) + (dy * dy) < size * size)
// 				mlx_pixel_put(mlx, win, x, y, 0xFFFF00);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_loop(mlx);
// }

// #include <stdlib.h>
// #include <math.h>
// #include <stdio.h>

// typedef struct	s_vars
// {
// 	void	*mlx;
// 	void	*win;
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// 	double	zoom;
// 	int		offset_x;
// 	int		offset_y;
// 	int		mouse_x;
// 	int		mouse_y;
// 	int		is_dragging;
// }				t_vars;

// typedef struct	s_point
// {
// 	double x;
// 	double y;
// }				t_point;

// #define WIDTH 800
// #define HEIGHT 800
// #define MAX_DEPTH 9
// #define ZOOM_FACTOR 1.2

// // Function to put a pixel on the image
// void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
// 	{
// 		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 		*(unsigned int*)dst = color;
// 	}
// }

// // Draw a filled triangle
// void	draw_triangle(t_vars *data, t_point p1, t_point p2, t_point p3, int color)
// {
// 	int min_x = fmax(0, fmin(fmin(p1.x, p2.x), p3.x));
// 	int min_y = fmax(0, fmin(fmin(p1.y, p2.y), p3.y));
// 	int max_x = fmin(WIDTH - 1, fmax(fmax(p1.x, p2.x), p3.x));
// 	int max_y = fmin(HEIGHT - 1, fmax(fmax(p1.y, p2.y), p3.y));
	
// 	for (int y = min_y; y <= max_y; y++)
// 	{
// 		for (int x = min_x; x <= max_x; x++)
// 		{
// 			// Barycentric coordinates to determine if point is in triangle
// 			double d = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);
// 			double a = ((p2.y - p3.y) * (x - p3.x) + (p3.x - p2.x) * (y - p3.y)) / d;
// 			double b = ((p3.y - p1.y) * (x - p3.x) + (p1.x - p3.x) * (y - p3.y)) / d;
// 			double c = 1 - a - b;
			
// 			if (a >= 0 && b >= 0 && c >= 0)
// 				my_mlx_pixel_put(data, x, y, color);
// 		}
// 	}
// }

// // Recursive function to draw the Sierpinski triangle
// void	draw_sierpinski(t_vars *data, t_point p1, t_point p2, t_point p3, int depth, int color)
// {
// 	// Apply zoom and offset
// 	t_point zoomed_p1 = {
// 		(p1.x * data->zoom) + data->offset_x,
// 		(p1.y * data->zoom) + data->offset_y
// 	};
// 	t_point zoomed_p2 = {
// 		(p2.x * data->zoom) + data->offset_x,
// 		(p2.y * data->zoom) + data->offset_y
// 	};
// 	t_point zoomed_p3 = {
// 		(p3.x * data->zoom) + data->offset_x,
// 		(p3.y * data->zoom) + data->offset_y
// 	};
	
// 	// Check if any point is on screen before continuing
// 	if ((zoomed_p1.x < 0 && zoomed_p2.x < 0 && zoomed_p3.x < 0) ||
// 		(zoomed_p1.x > WIDTH && zoomed_p2.x > WIDTH && zoomed_p3.x > WIDTH) ||
// 		(zoomed_p1.y < 0 && zoomed_p2.y < 0 && zoomed_p3.y < 0) ||
// 		(zoomed_p1.y > HEIGHT && zoomed_p2.y > HEIGHT && zoomed_p3.y > HEIGHT))
// 		return;
	
// 	// Calculate size of triangle to check for minimum size and early termination
// 	double size = sqrt(pow(zoomed_p2.x - zoomed_p1.x, 2) + pow(zoomed_p2.y - zoomed_p1.y, 2));
// 	if (size < 1)
// 		return;
	
// 	if (depth == 0)
// 	{
// 		draw_triangle(data, zoomed_p1, zoomed_p2, zoomed_p3, color);
// 		return;
// 	}
	
// 	// Find the midpoints of each side
// 	t_point mid1 = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
// 	t_point mid2 = {(p2.x + p3.x) / 2, (p2.y + p3.y) / 2};
// 	t_point mid3 = {(p3.x + p1.x) / 2, (p3.y + p1.y) / 2};
	
// 	// Draw the three smaller Sierpinski triangles (excluding the middle one)
// 	draw_sierpinski(data, p1, mid1, mid3, depth - 1, color);
// 	draw_sierpinski(data, mid1, p2, mid2, depth - 1, color);
// 	draw_sierpinski(data, mid3, mid2, p3, depth - 1, color);
// }

// // Draw everything
// void	draw_all(t_vars *vars)
// {
// 	// Clear the image
// 	for (int y = 0; y < HEIGHT; y++)
// 		for (int x = 0; x < WIDTH; x++)
// 			my_mlx_pixel_put(vars, x, y, 0x00000000);
	
// 	// Define the initial triangle
// 	t_point p1 = {WIDTH / 2, 50};
// 	t_point p2 = {50, HEIGHT - 50};
// 	t_point p3 = {WIDTH - 50, HEIGHT - 50};
	
// 	// Draw the fractal
// 	draw_sierpinski(vars, p1, p2, p3, MAX_DEPTH, 0x00FF00FF);
	
// 	// Display zoom level
// 	char zoom_str[100];
// 	sprintf(zoom_str, "Zoom: %.2fx", vars->zoom);
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
// 	mlx_string_put(vars->mlx, vars->win, 10, 20, 0x00FFFFFF, zoom_str);
// 	mlx_string_put(vars->mlx, vars->win, 10, 40, 0x00FFFFFF, "Scroll to zoom in/out");
// 	mlx_string_put(vars->mlx, vars->win, 10, 60, 0x00FFFFFF, "Click and drag to pan");
// 	mlx_string_put(vars->mlx, vars->win, 10, 80, 0x00FFFFFF, "Press 'R' to reset view");
// }

// // Key hook
// int		key_hook(int keycode, t_vars *vars)
// {
// 	if (keycode == 53) // ESC key
// 	{
// 		mlx_destroy_window(vars->mlx, vars->win);
// 		exit(0);
// 	}
// 	else if (keycode == 15) // 'R' key to reset view
// 	{
// 		vars->zoom = 1.0;
// 		vars->offset_x = 0;
// 		vars->offset_y = 0;
// 		draw_all(vars);
// 	}
// 	return (0);
// }

// // Mouse button hook
// int		mouse_hook(int button, int x, int y, t_vars *vars)
// {
// 	if (button == 4) // Scroll up (zoom in)
// 	{
// 		double prev_zoom = vars->zoom;
// 		vars->zoom *= ZOOM_FACTOR;
		
// 		// Adjust offset to zoom toward mouse position
// 		double zoom_diff = vars->zoom - prev_zoom;
// 		vars->offset_x -= (x - WIDTH/2) * zoom_diff;
// 		vars->offset_y -= (y - HEIGHT/2) * zoom_diff;
		
// 		draw_all(vars);
// 	}
// 	else if (button == 5) // Scroll down (zoom out)
// 	{
// 		double prev_zoom = vars->zoom;
// 		vars->zoom /= ZOOM_FACTOR;
// 		if (vars->zoom < 0.1)
// 			vars->zoom = 0.1;
			
// 		// Adjust offset to zoom toward mouse position
// 		double zoom_diff = vars->zoom - prev_zoom;
// 		vars->offset_x -= (x - WIDTH/2) * zoom_diff;
// 		vars->offset_y -= (y - HEIGHT/2) * zoom_diff;
		
// 		draw_all(vars);
// 	}
// 	else if (button == 1) // Left mouse button (start dragging)
// 	{
// 		vars->is_dragging = 1;
// 		vars->mouse_x = x;
// 		vars->mouse_y = y;
// 	}
// 	return (0);
// }

// // Mouse move hook
// int		mouse_move(int x, int y, t_vars *vars)
// {
// 	if (vars->is_dragging)
// 	{
// 		vars->offset_x += (x - vars->mouse_x);
// 		vars->offset_y += (y - vars->mouse_y);
// 		vars->mouse_x = x;
// 		vars->mouse_y = y;
// 		draw_all(vars);
// 	}
// 	return (0);
// }

// // Mouse release hook
// int		mouse_release(int button, int x, int y, t_vars *vars)
// {
// 	if (button == 1) // Left mouse button
// 		vars->is_dragging = 0;
// 	return (0);
// }

// // Close the window when the X button is clicked
// int		close_hook(t_vars *vars)
// {
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	exit(0);
// 	return (0);
// }

// int		main(void)
// {
// 	t_vars	vars;
	
// 	// Initialize mlx
// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Sierpinski Triangle - Interactive");
// 	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
// 	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	
// 	// Initialize zoom and offset
// 	vars.zoom = 1.0;
// 	vars.offset_x = 0;
// 	vars.offset_y = 0;
// 	vars.is_dragging = 0;
	
// 	// Draw the initial fractal
// 	draw_all(&vars);
	
// 	// Set up hooks
// 	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
// 	mlx_hook(vars.win, 4, 1L<<2, mouse_hook, &vars);
// 	mlx_hook(vars.win, 5, 1L<<3, mouse_release, &vars);
// 	mlx_hook(vars.win, 6, 1L<<6, mouse_move, &vars);
// 	mlx_hook(vars.win, 17, 1L<<17, close_hook, &vars);
	
// 	// Start the mlx loop
// 	mlx_loop(vars.mlx);
	
// 	return (0);
// }


int main()
{
	void	*mlx;
	void	*win;
	int		x, y;
	int		size = 400;
	int		pos_x = 100;
	int		pos_y = 100;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 800, "circle");
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (x > 200 - y / 2 && x < 200 + y / 2)
				mlx_pixel_put(mlx, win, x, y, 0xFF00FF);
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
}
