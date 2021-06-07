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
}

int	main_loop(t_canvas *canvas)
{
	draw_julia(canvas);
	return (0);
}

int	main(int argc, char **argv)
{
	t_canvas	canvas;

	(void)argc;
	(void)argv;
	printf("HELLO fractol\n");
	initialize_canvas(&canvas);
	mlx_hook(canvas.win, ClientMessage, 1L << 17, exit_canvas, &canvas);
	mlx_loop_hook(canvas.mlx, &main_loop, &canvas);
	mlx_loop(canvas.mlx);
}
