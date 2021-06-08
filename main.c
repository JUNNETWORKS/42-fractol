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
		&canvas->img.bits_per_pixel, &canvas->img.line_length, &canvas->img.endian);
	canvas->screen_height = HEIGHT;
	canvas->screen_width = WIDTH;
	canvas->max_r = 2;
	canvas->max_i = 2;
	canvas->min_r = -2;
	canvas->min_i = -2;
	canvas->zoom = 1;
}

int	main_loop(t_canvas *canvas)
{
	if (canvas->fractal_type == FRACTAL_JULIA)
		draw_julia(canvas);
	else if (canvas->fractal_type == FRACTAL_MANDELBROT)
		draw_mandelbrot(canvas);
	mlx_put_image_to_window(canvas->mlx, canvas->win, canvas->img.img, 0, 0);
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
	if (!ft_strncmp(argv[1], "mandelbrot", 11))
		canvas.fractal_type = FRACTAL_MANDELBROT;
	else if (!ft_strncmp(argv[1], "julia", 6))
		canvas.fractal_type = FRACTAL_JULIA;
	else
	{
		printf("You have to select fractal type\n"
			"- mandelbrot\n"
			"- julia\n");
		return (1);
	}
	mlx_hook(canvas.win, KeyPress, KeyPressMask, key_press_hook, &canvas);
	mlx_hook(canvas.win, ClientMessage, 1L << 17, exit_canvas, &canvas);
	mlx_mouse_hook(canvas.win, mouse_hook, &canvas);
	mlx_loop_hook(canvas.mlx, &main_loop, &canvas);
	mlx_loop(canvas.mlx);
}
