#include "minilibx/mlx.h"

// typedef struct s_data
// {
// 	void *img;
// 	char *addr;
// 	int bits_per_pixel;
// 	int line_length;
// 	int end;
// } t_data;

// void my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char *dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

// int main()
// {
// 	void *mlx;
// 	void *win;
// 	t_data img;
// 	int x, y;
// 	int size = 50;
// 	int pos_x = 100;
// 	int pos_y = 100;
// 	// int		r = 255;
// 	// int		g = 255;
// 	// int		b = 0;
// 	// int color = (r << 16) | (g << 8) | b;
// 	int color = 0xFFFF00;

// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 800, 400, "Hello MiniLibX!");
// 	// y = pos_y;
// 	// while (y < pos_y + size)
// 	// {
// 	// 	x = pos_x;
// 	// 	while (x < pos_x + size)
// 	// 	{
// 	// 		mlx_pixel_put(mlx, win, x, y, color);
// 	// 		x++;
// 	// 	}
// 	// 	y++;
// 	// }
// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.end);
// 	y = pos_y - size;
// 	while(y <= pos_y + size)
// 	{
// 		x = pos_x - size;
// 		while(x <= pos_x + size)
// 		{
// 			int dx = x - pos_x;
// 			int dy = y - pos_y;
// 			if (dx * dx + dy * dy <= size * size)
// 				my_mlx_pixel_put(&img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
// 	mlx_loop(mlx);
// }


// int main()
// {
// 	void	*mlx;
// 	void	*win;
// 	int		x, y;
// 	int		size = 200;
// 	int		pos_x = 300;
// 	int		pos_y = 300;
// 	// int		color = 0xFFFFF00;

// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 800, 600,"Hello MiniLibX!");
// 	y = pos_x - size;
// 	while (y < pos_y + size)
// 	{
// 		x = pos_x - size;
// 		while (x < pos_x + size)
// 		{
// 			int dx = x - pos_x;
// 			int dy = y - pos_y;
// 			if (dx * dx + dy * dy <= size * size)
// 			{
// 				int color = ((x * y) + (y * x)) % 0xFFFFFF;
// 				mlx_pixel_put(mlx, win, x, y, color);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_loop(mlx);
// }


// int main()
// {
// 	void	*mlx;
// 	void	*win;
// 	int		x, y;
// 	int		size = 200;
// 	int		pos_x = 900;
// 	int		pos_y = 600;
// 	// int		color = 0xFFFF00;

// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 1800, 1400, "Hello Mini!");
// 	y = pos_y - size;
// 	while (y < pos_y + size)
// 	{
// 		x = pos_x - size;
// 		while (x < pos_x + size)
// 		{
// 			int dx = x - pos_x;
// 			int dy = y - pos_y;
// 			if (dx * dx + dy * dy <= size * size) // This condition checks if the point is inside a circle of radius size
// 			{
// 				int color = ((x * x)+ (y * y) % 0xFFFF00);
// 				mlx_pixel_put(mlx, win, x, y, color);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_loop(mlx);
// }


typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	scale;
	double	offset_x;
	double	offset_y;
}				t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 1800 && y >= 0 && y < 1400)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_circle(t_data *data)
{
	int		screen_x;
	int		screen_y;
	int	world_x;
	int	world_y;
	// int		color = 0xFFFF00;
	int		size = 200;
	int		pos_x = 900;
	int		pos_y = 600;

	screen_y = -1;
	while (++screen_y < 1400)
	{
		screen_x = -1;
		while (++screen_x < 1800)
		{
			// Convert screen coordinates to world coordinates
			world_x = (screen_x - data->offset_x) / data->scale;
			world_y = (screen_y - data->offset_y) / data->scale;

			// Circle equation
			int dx = world_x - pos_x;
			int dy = world_y - pos_y;
			if (dx * dx + dy * dy <= size * size)
			{
				int color = ((world_x * world_x) + (world_y * world_y) % 0xFFFF00);
				my_mlx_pixel_put(data, screen_x, screen_y, color);
			}
		}
	}
}
int	mouse_hook(int button, int x, int y, t_data *data)
{
	double	world_x;
	double	world_y;
	double	zoom_factor;

	// Convert screen coordinates to world coordinates
	world_x = (x - data->offset_x) / data->scale;
	world_y = (y - data->offset_y) / data->scale;

	if (button == 4)	// Scroll up - zoom in
		zoom_factor = 1.1;
	else if (button == 5)	// Scroll down - zoom out
		zoom_factor = 0.9;
	else
		return (0);

	// Apply zoom relative to mouse position
	data->scale *= zoom_factor;
	data->offset_x = x - world_x * data->scale;
	data->offset_y = y - world_y * data->scale;

	// Redraw the image
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, 1800, 1400);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	draw_circle(data);  // You'll need to create this function
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}


int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1800, 1400, "Zoomable Circle");
	data.img = mlx_new_image(data.mlx, 1800, 1400);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	
	// Initial zoom settings
	data.scale = 1.0;
	data.offset_x = 0;
	data.offset_y = 0;

	// Set up hooks
	mlx_hook(data.win, 4, 1L<<2, mouse_hook, &data);  // Mouse press event
	mlx_loop(data.mlx);
	return (0);
}