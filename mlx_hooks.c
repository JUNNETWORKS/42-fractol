#include "fractol.h"

int	key_press_hook(int keycode, t_canvas *canvas)
{
	if (keycode == KEY_ESC)
		exit_canvas(canvas);
	return (0);
}

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int	mouse_hook(int button, int x, int y, t_canvas *canvas)
{
	double mouse_r;
	double mouse_i;
	double interpolation;

	mouse_r = (double)x / (WIDTH / (canvas->max_r - canvas->min_r)) + canvas->min_r;
	mouse_i = (double)y / (HEIGHT / (canvas->max_i - canvas->min_i)) * -1 + canvas->min_i;
	printf("button: %x, x: %d, y: %d\n", button, x, y);
	if (button == SCROLL_UP)
		interpolation = 1.0 / 0.8;
	else if (button == SCROLL_DOWN)
		interpolation = 1.0 / 1.2;
	else
		return (0);
	canvas->min_r = interpolate(mouse_r, canvas->min_r, interpolation);
	canvas->min_i = interpolate(mouse_i, canvas->min_i, interpolation);
	canvas->max_r = interpolate(mouse_r, canvas->max_r, interpolation);
	canvas->max_i = interpolate(mouse_i, canvas->max_i, interpolation);
	printf("canvas->zoom: %f\n", canvas->zoom);
	return (0);
}
