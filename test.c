#include "minilibx/mlx.h"
#include <math.h>
#include <stdlib.h>

// int main()
// {
// 	void	*mlx;
// 	void	*win;
// 	int		x, y;
// 	int		size = 400;
// 	int		pos_x = 100;
// 	int		pos_y = 100;

// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 800, 800, "circle");
// 	y = 0;
// 	while (y < size)
// 	{
// 		x = 0;
// 		while (x < size)
// 		{
// 			if (x > 200 - y / 2 && x < 200 + y / 2)
// 				mlx_pixel_put(mlx, win, x, y, 0xFF00FF);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_loop(mlx);
// }
#include <stdio.h>

// int key_press(int keycode, void *param)
// {
// 	printf("key is: %d\n", keycode);
// 	return (0);
// }

// int main()
// {
// 	void *mlx = mlx_init();
// 	void *win = mlx_new_window(mlx, 1000, 800, "what is the key?");
// 	mlx_key_hook(win, key_press, NULL);
// 	mlx_loop(mlx);
// }



int key_press(int keycode, void *param)
{
	printf("key is: %d\n", keycode);
	return (0);
}

int main()
{
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, 1000, 500, "check key");
	mlx_key_hook(win, key_press, NULL);
	mlx_loop(mlx);
}

