#include "fractol.h"

int	exit_canvas(t_canvas *canvas)
{
	mlx_destroy_window(canvas->mlx, canvas->win);
	exit(0);
}

void	initialize_canvas(t_canvas *canvas)
{
	canvas->mlx = mlx_init();
	canvas->win = mlx_new_window(canvas->mlx, WIDTH, HEIGHT, "fractol");
	canvas->img.img = mlx_new_image(canvas->mlx,
			WIDTH, HEIGHT);
	canvas->img.addr = mlx_get_data_addr(canvas->img.img,
			&canvas->img.bits_per_pixel,
			&canvas->img.line_length, &canvas->img.endian);
	canvas->max_re = 2;
	canvas->max_im = 2;
	canvas->min_re = -2;
	canvas->min_im = -2;
	canvas->max_iter = 100;
}

int	main_loop(t_canvas *canvas)
{
	(void)canvas;
	return (0);
}

bool	set_fractal_type(t_canvas *canvas, char *str)
{
	if (!ft_strncmp(str, "mandelbrot", 11))
		canvas->fractal_drawer = draw_mandelbrot;
	else if (!ft_strncmp(str, "julia", 6))
		canvas->fractal_drawer = draw_julia;
	else
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_canvas	canvas;

	if (argc != 2 || !set_fractal_type(&canvas, argv[1]))
	{
		printf("You have to select fractal type\n"
			"- mandelbrot\n"
			"- julia\n");
		return (1);
	}
	initialize_canvas(&canvas);
	canvas.fractal_drawer(&canvas);
	mlx_put_image_to_window(canvas.mlx, canvas.win, canvas.img.img, 0, 0);
	mlx_hook(canvas.win, KeyPress, KeyPressMask, key_press_hook, &canvas);
	mlx_hook(canvas.win, ClientMessage, 1L << 17, exit_canvas, &canvas);
	mlx_mouse_hook(canvas.win, mouse_hook, &canvas);
	mlx_loop_hook(canvas.mlx, &main_loop, &canvas);
	mlx_loop(canvas.mlx);
}
