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


int main()
{
	void	*mlx;
	void	*win;
	int		x, y;
	int		size = 200;
	int		pos_x = 300;
	int		pos_y = 300;
	// int		color = 0xFFFFF00;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600,"Hello MiniLibX!");
	y = pos_x - size;
	while (y < pos_y + size)
	{
		x = pos_x - size;
		while (x < pos_x + size)
		{
			int dx = x - pos_x;
			int dy = y - pos_y;
			if (dx * dx + dy * dy <= size * size)
			{
				int color = ((x * y) + (y * x)) % 0xFFFFFF;
				mlx_pixel_put(mlx, win, x, y, color);
			}
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
}

