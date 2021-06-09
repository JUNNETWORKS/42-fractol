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
	double	mouse_re;
	double	mouse_im;
	double	interpolation;

	mouse_re = (double)x
		/ (WIDTH / (canvas->max_re - canvas->min_re)) + canvas->min_re;
	mouse_im = (double)y
		/ (HEIGHT / (canvas->max_im - canvas->min_im)) * -1 + canvas->max_im;
	if (button == SCROLL_UP)
		interpolation = 1.0 / 0.8;
	else if (button == SCROLL_DOWN)
		interpolation = 1.0 / 1.2;
	else
		return (0);
	canvas->min_re = interpolate(mouse_re, canvas->min_re, interpolation);
	canvas->min_im = interpolate(mouse_im, canvas->min_im, interpolation);
	canvas->max_re = interpolate(mouse_re, canvas->max_re, interpolation);
	canvas->max_im = interpolate(mouse_im, canvas->max_im, interpolation);
	return (0);
}
