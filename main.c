#include "fractol.h"

int	exit_canvas(t_canvas *canvas)
{
	mlx_destroy_window(canvas->mlx, canvas->win);
	exit(0);
}

void	initialize_canvas(t_canvas *canvas)
{
	int max_width;
	int max_height;

	canvas->mlx = mlx_init();
	// mlx_get_screen_size(canvas->mlx, &max_width, &max_height);
	// TODO: とりあえずは800*800固定でやる
	max_width = 800;
	max_height = 800;
	canvas->win = mlx_new_window(canvas->mlx, max_width, max_height, "fractol");
	canvas->img.img = mlx_new_image(canvas->mlx,
		max_width, max_height);
	canvas->img.addr = mlx_get_data_addr(canvas->img.img,
		&canvas->img.bits_per_pixel, &canvas->img.line_length, &canvas->img.endian);
	canvas->screen_height = max_height;
	canvas->screen_width = max_width;
}

void update_mouse_position(t_canvas *canvas)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(canvas->mlx, canvas->win, &x, &y);
	canvas->mouse_x = x;
	canvas->mouse_y = y;
}

int	main_loop(t_canvas *canvas)
{
	update_mouse_position(canvas);
	printf("mouse: (%d, %d)\n", canvas->mouse_x, canvas->mouse_y);
	return (0);
}

int	main(int argc, char **argv)
{
	t_canvas	canvas;

	if (argc != 2)
	{
		printf("argc is invalid\n");
		return (1);
	}
	initialize_canvas(&canvas);
	if (!ft_strncmp(argv[1], "mandelbrot", 10))
		draw_mandelbrot(&canvas);
	else if (!ft_strncmp(argv[1], "julia", 5))
		draw_julia(&canvas);
	mlx_put_image_to_window(canvas.mlx, canvas.win, canvas.img.img, 0, 0);
	mlx_hook(canvas.win, KeyPress, KeyPressMask, key_press_hook, &canvas);
	mlx_hook(canvas.win, ClientMessage, 1L << 17, exit_canvas, &canvas);
	mlx_mouse_hook(canvas.win, mouse_hook, &canvas);
	mlx_loop_hook(canvas.mlx, &main_loop, &canvas);
	mlx_loop(canvas.mlx);
}
